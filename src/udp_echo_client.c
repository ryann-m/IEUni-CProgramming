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
 * Get the address info struct for the server.
 * @param address The server address.
 * @param port The server port.
 * @return The addrinfo struct.
 */
struct addrinfo *get_address_info(const char *address, const char *port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;      // IPv4
  hints.ai_socktype = SOCK_DGRAM; // UDP socket
  struct addrinfo *address_info;
  int res = getaddrinfo(address, port, &hints, &address_info);
  if (res != 0) {
    fprintf(stderr, "getaddrinfo() failed. (%s)\n", gai_strerror(res));
    exit(1);
  }
  return address_info;
}

/**
 * Create a UDP socket.
 * @param address_info The address info struct.
 * @return The created socket.
 */
SOCKET create_socket(struct addrinfo *address_info) {
  printf("Creating UDP socket...\n");
  SOCKET sock = socket(address_info->ai_family, address_info->ai_socktype,
                       address_info->ai_protocol);
  if (!ISVALIDSOCKET(sock)) {
    fprintf(stderr, "socket() failed. (%s)\n", strerror(errno));
    exit(1);
  }
  return sock;
}

/**
 * Send a message to the server and receive the echo response.
 * @param sock The UDP socket.
 * @param server_address The server address structure.
 * @param message The message to send.
 */
void send_and_receive(SOCKET sock, struct addrinfo *server_address,
                      const char *message) {
  printf("Sending: '%s'\n", message);
  // Send message to server
  int bytes_sent = sendto(sock, message, strlen(message), 0,
                          server_address->ai_addr, server_address->ai_addrlen);
  if (bytes_sent < 0) {
    fprintf(stderr, "sendto() failed. (%s)\n", strerror(errno));
    return;
  }
  printf("Sent %d bytes.\n", bytes_sent);
  // Receive echo response from server
  char buffer[BUFFER_SIZE];
  struct sockaddr_storage server_storage;
  socklen_t server_len = sizeof(server_storage);
  printf("Waiting for response...\n");
  int bytes_received =
      recvfrom(sock, buffer, BUFFER_SIZE - 1, 0,
               (struct sockaddr *)&server_storage, &server_len);
  if (bytes_received < 0) {
    fprintf(stderr, "recvfrom() failed. (%s)\n", strerror(errno));
    return;
  }
  buffer[bytes_received] = '\0'; // Null-terminate the received data
  printf("Received %d bytes: '%s'\n\n", bytes_received, buffer);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <server_address> [message]\n", argv[0]);
    fprintf(stderr, "Example: %s 127.0.0.1 \"Hello, UDP!\"\n", argv[0]);
    return 1;
  }
  const char *server_address = argv[1];
  struct addrinfo *address_info = get_address_info(server_address, "8080");
  SOCKET sock = create_socket(address_info);
  printf("Connected to server %s:8080\n", server_address);

  send_and_receive(sock, address_info, argv[2]);
  printf("\nClosing socket...\n");
  freeaddrinfo(address_info);
  CLOSESOCKET(sock);
  printf("Finished.\n");
  return 0;
}