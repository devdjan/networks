#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // to use close() func
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define port   1100

int main() {
  // create the socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // check if we can create a socket
  if(network_socket == -1){
    perror("Error occured, can't create a socket\n");
    return EXIT_FAILURE;
  }

  // specify an address for the socket
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port); // specified the port we connect remotely
  server_address.sin_addr.s_addr = INADDR_ANY;   // any address on the local machine

  // check the status of connection, we will use sys/socket func
  int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // check, can we connect to socket
  if(connection_status == -1){
    perror("Connection Error");
    close(network_socket);
    return EXIT_FAILURE;
  }

  // receive data from the server
  char server_response[256];
  recv(network_socket, &server_response, sizeof(server_response), 0);

  // print out the servers response
  printf("The server has sent the data: %s\n", server_response);

  // close the socket connection after we printed out the servers response
  close(network_socket);

  return 0;
}
