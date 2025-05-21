#ifndef CONNECT_H
#define CONNECT_H

#include <netinet/in.h>

#define MAX_CONNECTIONS 10 // Giới hạn số lượng kết nối lưu được

typedef struct // cấu trúc dùng cho 1 kết nối
{
    int socketFd; // fd của kết nối
    struct sockaddr_in addr; //địa chỉ peer
} Connection;

void initConnectionList(); //hàm khởi tạo danh sách kết nối

int addConnection(int socketFd, struct sockaddr_in addr); //hàm thêm kết nối vào danh sách

void removeConnection(int index); // hàm xoá kết nối khỏi danh sách

void closeAllConnections(); // đóng tất cả kết nối

void listConnections(); // in danh sách kết nối

int getSocketFdByIndex(int index); // <- đảm bảo có khai báo này

#endif




