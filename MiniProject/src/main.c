#include "server.h"
#include "cli.h"
#include "connect.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define DEFAULT_PORT 7000

// Xử lý Ctrl+C
void handle_sigint(int sig) {
    printf("\nCaught signal %d, shutting down...\n", sig);
    closeAllConnections();
    exit(0);
}

int main(int argc, char* argv[]) {
    int port = DEFAULT_PORT;

    // Nếu người dùng chỉ định cổng từ dòng lệnh
    if (argc == 2) {
        port = atoi(argv[1]);
    }

    signal(SIGINT, handle_sigint);  // Đăng ký xử lý Ctrl+C

    initConnectionList();

    // Khởi động server
    if (startServer(port) != 0) {
        fprintf(stderr, "Failed to start server on port %d\n", port);
        return 1;
    }

    printf("Server started on port %d.\n", port);

    // Tạo thread để lắng nghe server
    pthread_t serverThread;
    if (pthread_create(&serverThread, NULL, serverListener, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Xử lý lệnh người dùng
    handleUserInput();

    // Chờ thread server kết thúc (thường không xảy ra trừ khi thoát)
    pthread_join(serverThread, NULL);
    return 0;
}
