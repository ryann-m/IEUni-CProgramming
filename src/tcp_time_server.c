#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
/**
 * Get the address info struct for binding the server socket.
 * @param port The port to bind to.
 * @return The addrinfo struct.
 */
struct addrinfo *get_bind_address(const char *port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP socket
  hints.ai_flags = AI_PASSIVE;     // For wildcard IP address
  struct addrinfo *bind_address;
  // 0 means any local address
  getaddrinfo(0, port, &hints, &bind_address);
  return bind_address;
}

/**
 * Create a socket.
 * @param address_info The address info struct.
 * @return The created socket.
 */
SOCKET create_socket(struct addrinfo *address_info) {
  printf("Creating socket...\n");
  SOCKET sock;
  sock = socket(address_info->ai_family, address_info->ai_socktype,
                address_info->ai_protocol);
  if (!ISVALIDSOCKET(sock)) {
    fprintf(stderr, "socket() failed. (%s)\n", strerror(errno));
    exit(1);
  }
  return sock;
}

/**
 * Bind the socket to the address.
 * @param sock The socket to bind.
 * @param address_info The address info struct.
 */
void bind_socket(SOCKET sock, struct addrinfo *address_info) {
  printf("Binding socket to local address...\n");
  if (bind(sock, address_info->ai_addr, address_info->ai_addrlen)) {
    fprintf(stderr, "bind() failed. (%s)\n", strerror(errno));
    exit(1);
  }
}
/**
 * Create a listening socket.
 * @param port The port to bind to.
 * @return The listening socket.
 */
SOCKET create_listening_socket(const char *port) {
  struct addrinfo *bind_address = get_bind_address(port);
  SOCKET socket_listen = create_socket(bind_address);
  bind_socket(socket_listen, bind_address);
  freeaddrinfo(bind_address);
  printf("Listening on port %s...\n", port);
  if (listen(socket_listen, 10) < 0) {
    fprintf(stderr, "listen() failed. (%s)\n", strerror(errno));
    exit(1);
  }
  return socket_listen;
}

/**
 * Accept a client connection.
 * @param socket_listen The listening socket.
 * @return The client socket.
 */
SOCKET accept_client(SOCKET socket_listen) {
  printf("Waiting for connection...\n");
  struct sockaddr_storage client_address;
  socklen_t client_len = sizeof(client_address);
  SOCKET socket_client =
      accept(socket_listen, (struct sockaddr *)&client_address, &client_len);
  if (!ISVALIDSOCKET(socket_client)) {
    fprintf(stderr, "accept() failed. (%d)\n", errno);
    return -1;
  }

  printf("Client is connected... ");
  char client_address_str[100];
  const size_t buffer_size = sizeof(client_address_str);
  getnameinfo((struct sockaddr *)&client_address, client_len,
              client_address_str, buffer_size, 0, 0, NI_NUMERICHOST);
  printf("%s\n", client_address_str);

  return socket_client;
}

/**
 * Handle the client request by sending the local time.
 * @param socket_client The client socket.
 */
void handle_client(SOCKET socket_client) {
  printf("Reading request...\n");
  char request[1024];
  int bytes_received = recv(socket_client, request, 1024, 0);
  printf("Received %d bytes.\n", bytes_received);
  // We ignore the content of the request.

  printf("Sending response...\n");
  const char *response = "HTTP/1.1 200 OK\r\n"
                         "Connection: close\r\n"
                         "Content-Type: text/plain\r\n\r\n"
                         "Local time is: ";
  int bytes_sent = send(socket_client, response, strlen(response), 0);
  printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

  time_t timer;
  time(&timer);
  char *time_msg = ctime(&timer);
  bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
  printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_msg));
}

int main() {
  SOCKET socket_listen = create_listening_socket("8080");

  /* Accept and handle clients in a loop. Each client is handled then the
     connection is closed; the listening socket stays open to accept more. */

  while (1) {
    SOCKET socket_client = accept_client(socket_listen);
    if (!ISVALIDSOCKET(socket_client)) {
      continue;
    }

    handle_client(socket_client);
    printf("Closing connection...\n");

    CLOSESOCKET(socket_client);
  }
}