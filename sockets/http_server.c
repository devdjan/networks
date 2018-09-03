#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // close func
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define port   1212

int main() {

  // create file pointer to hold the data
  FILE *html_data;
  html_data = fopen("index.html", "r");

  char response_data[1024];
  fgets(response_data, 1024, html_data); // string array | size(amount of text) |

  // http header response for resource we have requested
  char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
  strcat(http_header, response_data);

  //creation of socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // defining the address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY;


  // bind()
  bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  // listen()
  listen(server_socket, 5);

  // client socket
  int client_socket;
  while(1) {
    client_socket = accept(server_socket, NULL, NULL);
    send(client_socket, http_header, sizeof(http_header), 0);
    close(client_socket);
  }

  return 0;
}
