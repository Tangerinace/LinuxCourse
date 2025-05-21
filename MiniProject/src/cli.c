#include "cli.h"
#include "client.h"
#include "connect.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h> 


#define MAX_COMMAND_LEN 1024
extern void* receiveMessages(void* arg);

void handleUserInput() {
    char command[MAX_COMMAND_LEN];

    while (1) {
        printf("P2P> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "connect", 7) == 0) {
            char ip[INET_ADDRSTRLEN];
            int port;
            if (sscanf(command + 7, "%s %d", ip, &port) == 2) {
                int sockfd = connectPeer(ip, port);
                if (sockfd >= 0) {
                    struct sockaddr_in addr;
                    addr.sin_family = AF_INET;
                    addr.sin_port = htons(port);
                    inet_pton(AF_INET, ip, &addr.sin_addr);
                    addConnection(sockfd, addr);


                    pthread_t recvThread;
                    int* sockPtr = malloc(sizeof(int));
                    *sockPtr = sockfd;
                    pthread_create(&recvThread, NULL, receiveMessages, sockPtr);
                    pthread_detach(recvThread); // tự động thu hồi tài nguyên
                }
            } else {
                printf("Usage: connect <IP> <Port>\n");
            }

        } else if (strncmp(command, "list", 4) == 0) {
            listConnections();

        } else if (strncmp(command, "send", 4) == 0) {
            int index;
            char message[1024];
            if (sscanf(command + 5, "%d %[^\n]", &index, message) == 2) {
                int sockfd = getSocketFdByIndex(index);
                if (sockfd >= 0) {
                    sendMessage(sockfd, message);
                } else {
                    printf("Invalid connection index.\n");
                }
            } else {
                printf("Usage: send <index> <message>\n");
            }

        } else if (strncmp(command, "terminate", 9) == 0) {
            int index;
            if (sscanf(command + 10, "%d", &index) == 1) {
                removeConnection(index);
            } else {
                printf("Usage: terminate <index>\n");
            }


        } else if (strncmp(command, "exit", 4) == 0) {
            closeAllConnections();
            printf("Exiting program.\n");
            exit(0);
        }  else if (strncmp(command, "help", 4) == 0) {
    printf("Available commands:\n");
    printf("  connect <IP> <PORT>     - Connect to a peer\n");
    printf("  list                    - List active connections\n");
    printf("  send <INDEX> <MESSAGE>  - Send a message to a connection\n");
    printf("  terminate <INDEX>       - Terminate a connection\n");
    printf("  exit                    - Exit the application\n");
    printf("  help                    - Show this help message\n");
 }
    }
}


