/**
* A client for a echo service using IPv4. Based on example from "TCP/IP Sockets
* in C" by Donahoo, Calvert.
*
* @author Donahoo, Calvert, Acuna
* @version 1.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 512

void ExitClient(char* msg) {
    printf(msg);
    exit(1);
}

void HandleTCPClient(int clntSocket);

int main(int argc, char *argv[]) {
    
    // 1) Fetch client parameters (server IP, server port, text message).
    if (argc < 3 || argc > 4)
    ExitClient("Parameter(s): <Server Address> <Echo Word> [<Server Port>]");

    char* server_ip_str = argv[1];
    char* echo_text = argv[2]; 
    in_port_t servPort;

    if(argc == 4)
        servPort = atoi(argv[3]);
    else
        servPort = 7; //typical echo port

    
    // 2) Create a socket using TCP.
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0)
      ExitClient("socket(): failed creation");

    
    // 3) Construct the server address struct
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;          // IPv4

    int rtnVal = inet_pton(AF_INET, server_ip_str, &serverAddr.sin_addr.s_addr);
    if (rtnVal == 0)
        ExitClient("inet_pton(): found invalid ip address");
    else if (rtnVal < 0)
        ExitClient("inet_pton(): found error when parsing address");
    serverAddr.sin_port = htons(servPort);
    

    // 4) Establish the connection to the server.
    if (connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        ExitClient("connect(): failed");


    // 5) Send message.
    size_t echo_text_len = strlen(echo_text);
    ssize_t numBytes = send(sock, echo_text, echo_text_len, 0);
    if (numBytes < 0)
        ExitClient("send(): failed to send message");
    else if (numBytes != echo_text_len)
        ExitClient("send(): sent unexpected number of bytes");

    
    // 6) Receive message.
    unsigned int bytes_recieved = 0;
    printf("Received: ");
    while (bytes_recieved < echo_text_len) {
      char buffer[BUFFER_SIZE];
      
      numBytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
      if (numBytes < 0)
          ExitClient("recv(): failed");
      else if (numBytes == 0)
          ExitClient("recv(): connection closed prematurely");
      bytes_recieved += numBytes;
      buffer[numBytes] = '\0';
      fputs(buffer, stdout);
    }
    printf("\n");
    
    // 7) Close the socket.

    close(sock);
    exit(0);
}
