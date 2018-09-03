#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/uio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define port   8989
char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>WebServak</title>\r\n"
"<style>body {background-color: #FFFFFF}</style></head>\r\n"
"<body><center><h1>Hello World!</h1><br>\r\n"
"<img src=\"logo.svg\"></center></body></html>\r\n";

int main(int argc, char const *argv[]) {
  struct sockaddr_in server_addr, client_addr;
  socklen_t sin_len = sizeof(client_addr);
  int fd_server, fd_client; // will retirn value from socket function
  char buf[2048];
  int fdimg; // will hold files descriptor which we open
  int on = 1;

  fd_server = socket(AF_INET, SOCK_STREAM, 0);
  if (fd_server < 0) {
    perror("Socket");
    exit(1);
  }

  // set socket properties
  setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

  // define the address of the server_addr
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // bind()
  if (bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
    perror("Error: Bind");
    close(fd_server);
    exit(EXIT_FAILURE);
  }

  // listen()
  if (listen(fd_server, 10) == -1) {
    perror("Error: Listening");
    close(fd_server);
    exit(EXIT_FAILURE);
  }

  while (1) {
    fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);

    if (fd_client == -1) {
      perror("Connection is failed...\n");
      continue;
    }

    printf("Got connection with client...\n");

    if (!fork()) {
      /* child process */
      close(fd_server);
      memset(buf, 0, 2048);
      read(fd_client, buf, 2047);

      printf("%s\n", buf);

      if(!strncmp(buf, "GET /favicon.ico", 16)) {
        fdimg = open("favicon.ico", O_RDONLY);
        sendfile(fd_client, fdimg, NULL, 16000);
        close(fdimg);
      }

      else if(!strncmp(buf, "GET /logo.svg", 16)) {
        fdimg = open("logo.svg", O_RDONLY);
        sendfile(fd_client, fdimg, NULL, 5000);
        close(fdimg);
      }
      else
        write(fd_client, webpage, sizeof(webpage) - 1);
      close(fd_client);
      printf("Closing....\n");
      exit(0);
    }
    /* parent process */
    close(fd_client);


  }

  return 0;
}
