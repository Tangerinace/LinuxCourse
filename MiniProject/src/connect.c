#include "connect.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>


static Connection connections[MAX_CONNECTIONS];
static int connectionCount = 0;

void initConnectionList() {
    memset(connections, 0, sizeof(connections));
    connectionCount = 0;
}

int addConnection(int socketFd, struct sockaddr_in addr) {
    if (connectionCount >= MAX_CONNECTIONS) {
        fprintf(stderr, "Max connections (%d) reached. Cannot add new connection.\n", MAX_CONNECTIONS);
        return -1;
    }

    connections[connectionCount].socketFd = socketFd;
    connections[connectionCount].addr = addr;
    connectionCount++;
    return 0;
}

void removeConnection(int index) {
    if (index < 0 || index >= connectionCount) {
        fprintf(stderr, "Invalid connection index\n");
        return;
    }

    close(connections[index].socketFd);
    for (int i = index; i < connectionCount - 1; i++) {
        connections[i] = connections[i + 1];
    }
    connectionCount--;
}

void closeAllConnections() {
    for (int i = 0; i < connectionCount; i++) {
        close(connections[i].socketFd);
    }
    connectionCount = 0;
}

void listConnections() {
    printf("Active Connections (%d):\n", connectionCount);
    for (int i = 0; i < connectionCount; i++) {
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &connections[i].addr.sin_addr, ipStr, sizeof(ipStr));
        int port = ntohs(connections[i].addr.sin_port);
        printf("[%d] %s:%d\n", i, ipStr, port);
    }
}

int getSocketFdByIndex(int index) {
    if (index < 0 || index >= connectionCount) {
        fprintf(stderr, "Invalid connection index\n");
        return -1;
    }
    return connections[index].socketFd;



}
