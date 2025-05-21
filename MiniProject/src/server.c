#include "server.h"
#include "connect.h" // Cần để gọi addConnection()
#include "utils.h"   // Cần nếu dùng getIPAddressString()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

#define BACKLOG 10 // Số lượng kết nối chờ tối đa

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

extern void* receiveMessages(void* arg);


// Biến toàn cục
static int listenSocket = -1;
static int listenPort = -1;

// Hàm khởi tạo server socket, bind và listen
int startServer(int port) {
    struct sockaddr_in addr;

    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == -1)
        handle_error("socket()");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listenSocket, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        handle_error("bind()");

    if (listen(listenSocket, BACKLOG) == -1)
        handle_error("listen()");

    listenPort = port;
    return 0;
}

// Luồng lắng nghe kết nối đến từ client khác
void* serverListener(void* arg) {
    (void)arg; // tránh cảnh báo unused parameter

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t addr_len = sizeof(clientAddr);

        int clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &addr_len);
        if (clientSocket == -1) {
            perror("accept()");
            continue;
        }

        char ipStr[INET_ADDRSTRLEN];
        if (!inet_ntop(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr))) {
            perror("inet_ntop()");
            close(clientSocket);
            continue;
        }

        int clientPort = ntohs(clientAddr.sin_port);
        printf("Connection from: %s:%d\n", ipStr, clientPort);

        // Thêm vào danh sách kết nối
        addConnection(clientSocket, clientAddr);
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, ip_str, sizeof(ip_str));
        int client_port = ntohs(clientAddr.sin_port);
        printf("Connection from: %s:%d\n", ip_str, client_port);

        pthread_t recvThread;
        int* sockPtr = malloc(sizeof(int));
        *sockPtr = clientSocket;
        pthread_create(&recvThread, NULL, receiveMessages, sockPtr);
        pthread_detach(recvThread);

    }

    return NULL;
}

// Trả về port server đang lắng nghe
int getListenport() {
    return listenPort;
}
