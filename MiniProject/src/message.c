#include "message.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int sendMessage(int socketFd, const char* message){
    int length = strlen(message);
    if(length >= MAX_MESSAGE_LENGTH){
        fprintf(stderr, "Message too long to send\n");
        return -1;
    }

    int sent = send(socketFd, message, length + 1, 0);
    if(sent == -1){
        perror("send");
        return -1;
    }

    return 0;
}

int receiveMessage(int socketFd, char* buffer, int bufferSize){
    memset(buffer, 0, bufferSize);

    int received = recv(socketFd, buffer, bufferSize - 1, 0);
    if(received == -1){
        perror("recv");
        return -1;

    } else if(received == 0){
        printf("Connection closed by peer\n");
        return 0;
    }
    
    buffer[received] = '\0';
    return received;
}