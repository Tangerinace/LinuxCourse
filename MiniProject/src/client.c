#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


int connectPeer(const char* ip,int port){
    int sockFd;
    struct sockaddr_in serverAddr;
    
    sockFd = socket(AF_INET,SOCK_STREAM,0);
    if(sockFd == -1)
        handle_error("socket()");

    memset(&serverAddr,0 , sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if(inet_pton(AF_INET,ip,&serverAddr.sin_addr) <= 0) {
        fprintf(stderr,"Invalid IP address: %s\n",ip);
        close(sockFd);
        return -1;
    }
    if(connect(sockFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) ==-1)
        handle_error("connect()");

    printf("Connect to %s:%d\n",ip,port);
    return sockFd;

}
void* receiveMessages(void* arg) {
    int sockfd = *(int*)arg;
    free(arg);

    char buffer[1024];
    while (1) {
        int received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) break;
        buffer[received] = '\0';
        printf("\n[Received]: %s\nP2P> ", buffer);
        fflush(stdout);
    }
    close(sockfd);
    return NULL;
}


