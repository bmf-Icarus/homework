/**
* A server for a echo service using IPv4. Based on example from "TCP/IP Sockets
* in C" by Donahoo, Calvert.
*
* @author Donahoo, Calvert, Acuna
* @version 1.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define RCVBUFSIZE 32   

static const int MAXPENDING = 5;

void ExitClient(char* msg) {
    printf(msg);
    exit(1);
}

void handle_client_socket(int clntSocket);

int main(int argc, char *argv[]) {

  // 1) Fetch server parameters (server port).   
  if (argc != 2)
    ExitClient("Parameter(s): <Server Port>");

  in_port_t servPort = atoi(argv[1]);

  // 2) Create a socket using TCP.
  int servSock;
  if ((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    ExitClient("socket(): failed creation");

  //3) Construct the server address struct
  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(servPort);

  // 4) Bind to the local address
  if (bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
    ExitClient("bind() failed");

  // 5) Mark the socket so it will listen for incoming connections
  if (listen(servSock, MAXPENDING) < 0)
    ExitClient("listen() failed");

  for (;;) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 6) Wait for a client to connect
    int clntSock = accept(servSock, (struct sockaddr *) &client_addr, &client_addr_len);
    if (clntSock < 0)
      ExitClient("accept() failed");

    // 7) Handle client connection.
    char client_name[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_name,
        sizeof(client_name)) != NULL)
      printf("Handling client %s/%d\n", client_name, ntohs(client_addr.sin_port));
    else
      puts("Unable to get client address");

    handle_client_socket(clntSock);
  }
}

void handle_client_socket(int clntSocket) {
  char buffer[RCVBUFSIZE];

  //1) Receive message.
  ssize_t numBytesRcvd = recv(clntSocket, buffer, RCVBUFSIZE, 0);
  if (numBytesRcvd < 0)
    ExitClient("recv() failed");

  while (numBytesRcvd > 0) {
    //2) Reply by sending back (part of) the message.
    ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
    if (numBytesSent < 0)
      ExitClient("send() failed");
    else if (numBytesSent != numBytesRcvd)
      ExitClient("send(): sent unexpected number of bytes");

    //3) Receive message (if exists).
    numBytesRcvd = recv(clntSocket, buffer, RCVBUFSIZE, 0);
    if (numBytesRcvd < 0)
      ExitClient("recv() failed");
  }

  //4) Close the socket.
  close(clntSocket);
}
