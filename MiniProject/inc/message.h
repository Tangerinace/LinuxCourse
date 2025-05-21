#ifndef MESSAGE_H
#define MESSAGE_H

#include <netinet/in.h>

#define MAX_MESSAGE_LENGTH 1024 // kích thước của một tin nhắn

int sendMessage(int socketFd, const char*message); // nhận tin nhắn từ socket và lưu vào buffer
//buffer đủ lớn để chứa max_message_length
// trả về số byet nhận được, hoặc -1 nếu lỗi

int receiveMessage(int socketFd, char* buffer, int bufferSize);

#endif

