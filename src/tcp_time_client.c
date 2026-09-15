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
 * Get the address info struct for connecting to the server.
 * @param address The server address.
 * @param port The server port.
 * @return The addrinfo struct.
 */
struct addrinfo *get_address_info(const char *address, const char *port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;       // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP socket
  struct addrinfo *address_info;
  int res = getaddrinfo(address, port, &hints, &address_info);
  if (res != 0) {
    fprintf(stderr, "getaddrinfo() failed. (%s)\n", gai_strerror(res));
    exit(1);
  }
  return address_info;
}

/**
 * Create a socket and connect to the server.
 * @param address_info The address info struct.
 * @return The created socket.
 */
SOCKET create_socket(struct addrinfo *address_info) {

  SOCKET sock = socket(address_info->ai_family, address_info->ai_socktype,
                       address_info->ai_protocol);
  if (!ISVALIDSOCKET(sock)) {
    fprintf(stderr, "socket() failed. (%s)\n", strerror(errno));
    exit(1);
  }

  return sock;
}

/**
 * Connect the socket to the server.
 * @param sock The socket to connect.
 * @param address_info The address info struct.
 */
void connect_to_server(SOCKET sock, struct addrinfo *address_info) {
  printf("Connecting...\n");
  if (connect(sock, address_info->ai_addr, address_info->ai_addrlen) < 0) {
    fprintf(stderr, "connect() failed. (%s)\n", strerror(errno));
    CLOSESOCKET(sock);
    exit(1);
  }
  printf("Connected.\n");
}

/**
 * Send an HTTP GET request to the server.
 * @param sock The socket connected to the server.
 */
void send_http_request(SOCKET sock) {
  const char *request = "GET / HTTP/1.1\r\n"
                        "Host: localhost\r\n"
                        "Connection: close\r\n\r\n";
  send(sock, request, strlen(request), 0);
}

/**
 * Receive the HTTP response from the server.
 * @param sock The socket connected to the server.
 * @return The received HTTP response as a string.
 */
const char *receive_http(SOCKET sock) {
  static char response[4096];
  int total_bytes_received = 0;
  int bytes_received;
  while ((bytes_received =
              recv(sock, response + total_bytes_received,
                   sizeof(response) - total_bytes_received - 1, 0)) > 0) {
    total_bytes_received += bytes_received;
  }
  response[total_bytes_received] = '\0'; // Null-terminate the string
  return response;
}

int main(int argc, char *argv[]) {
  char *server_address = argc >= 2 ? argv[1] : "127.0.0.1";
  struct addrinfo *address_info = get_address_info(server_address, "8080");
  SOCKET socket = create_socket(address_info);
  connect_to_server(socket, address_info);
  freeaddrinfo(address_info);
  send_http_request(socket);
  const char *http_page = receive_http(socket);
  printf("Received:\n%s\n", http_page);
  printf("Closing connection...\n");
  close(socket);
  printf("Finished.\n");
  return 0;
}