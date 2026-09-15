#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define BUFFER_SIZE 1024

/**
 * Get the address info struct for binding the UDP server socket.
 * @param port The port to bind to.
 * @return The addrinfo struct.
 */
struct addrinfo *get_bind_address(const char *port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;      // IPv4
  hints.ai_socktype = SOCK_DGRAM; // UDP socket
  hints.ai_flags = AI_PASSIVE;    // For wildcard IP address
  struct addrinfo *bind_address;
  getaddrinfo(0, port, &hints, &bind_address);
  return bind_address;
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
 * Create a UDP socket and bind it to a port.
 * @param port The port to bind to.
 * @return The UDP socket.
 */
SOCKET create_udp_socket(const char *port) {
  struct addrinfo *bind_address = get_bind_address(port);
  printf("Creating UDP socket on port %s...\n", port);
  SOCKET sock;
  sock = socket(bind_address->ai_family, bind_address->ai_socktype,
                bind_address->ai_protocol);
  if (!ISVALIDSOCKET(sock)) {
    fprintf(stderr, "socket() failed. (%s)\n", strerror(errno));
    exit(1);
  }
  bind_socket(sock, bind_address);
  freeaddrinfo(bind_address);
  return sock;
}

/**
 * Print client address information.
 * @param client_address The client address structure.
 * @param client_len The length of the client address structure.
 */
void print_client_info(struct sockaddr_storage *client_address,
                       socklen_t client_len) {
  char client_address_str[100];
  char client_port_str[100];
  getnameinfo((struct sockaddr *)client_address, client_len, client_address_str,
              sizeof(client_address_str), client_port_str,
              sizeof(client_port_str), NI_NUMERICHOST | NI_NUMERICSERV);
  printf("Client address: %s:%s\n", client_address_str, client_port_str);
}

/**
 * Receive a message from a client.
 * @param socket_udp The UDP socket.
 * @param client_address The client address structure to fill.
 * @param client_len The length of the client address structure to fill.
 * @return The received message (dynamically allocated, must be freed).
 */
char *receive_message(SOCKET socket_udp,
                      struct sockaddr_storage *client_address,
                      socklen_t *client_len) {
  char *buffer = (char *)malloc(BUFFER_SIZE);
  // Receive data from client
  *client_len = sizeof(*client_address); // Maximum size of client address
  int bytes_received = recvfrom(socket_udp, buffer, BUFFER_SIZE - 1, 0,
                                (struct sockaddr *)client_address, client_len);
  if (bytes_received < 0) {
    fprintf(stderr, "recvfrom() failed. (%s)\n", strerror(errno));
    free(buffer);
    return NULL;
  }
  buffer[bytes_received] = '\0'; // Null-terminate the received data
                                 // Get client address as string
  print_client_info(client_address, *client_len);
  printf("Received %d bytes: '%s'\n", bytes_received, buffer);
  return buffer;
}

/**
 * Echo the received message back to the client.
 * @param socket_udp The UDP socket.
 * @param client_address The client address structure.
 * @param client_len The length of the client address structure.
 * @param buffer The message to echo.
 * @return The number of bytes sent.
 */
int echo_message(SOCKET socket_udp, struct sockaddr_storage *client_address,
                 socklen_t client_len, char *buffer) {
  if (buffer == NULL || client_address == NULL) {
    return -1;
  }
  printf("Echoing message back...\n");
  size_t message_size = strlen(buffer);
  int bytes_sent = sendto(socket_udp, buffer, message_size, 0,
                          (struct sockaddr *)client_address, client_len);
  if (bytes_sent >= 0) {
    printf("Sent %d bytes back to client.\n\n", bytes_sent);
  } else {
    fprintf(stderr, "sendto() failed. (%s)\n", strerror(errno));
  }
  return bytes_sent;
}

int main() {
  SOCKET socket_udp = create_udp_socket("8080");
  printf("UDP Echo Server is running...\n");
  printf("Waiting for messages...\n");
  while (1) {
    struct sockaddr_storage client_address; // Filled by receive_message
    socklen_t client_len;                   // Filled by receive_message
    char *buffer = receive_message(socket_udp, &client_address, &client_len);
    int bytes_sent =
        echo_message(socket_udp, &client_address, client_len, buffer);
    free(buffer);
  }
  // Note: This server runs indefinitely. Use Ctrl+C to stop it.
  CLOSESOCKET(socket_udp);
  printf("Finished.\n");
  return 0;
}