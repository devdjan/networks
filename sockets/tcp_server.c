#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define port   1100

int main(){

  char server_message[256] = "You have reached the server";

  // create the server socket or define the server address
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if(server_socket == -1){
    perror("Error while creating the socket");
    exit(EXIT_FAILURE);
  }

  // whie we are assigning to our structure PORT, etc. we should clear it using memset
  //memset(&server_address, 0, size_of(server_address));

  // define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY; // any address on the local machine

  // call the bind() function
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // call listen() func to start listen for connection
  listen(server_socket, 5);

  // listen to connctins and accept them
  int client_socket = accept(server_socket, NULL, NULL);

  // let's try to sent a message
  send(client_socket, server_message, sizeof(server_message), 0);

  // close the connection
  close(server_socket);

}
