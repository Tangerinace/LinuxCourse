#ifndef CLIENT_H
#define CLIENT_H



int connectPeer(const char* ip, int port);
// vd khi bạn gõ lệnh connect 192.168.126.100 7000 thì hàm sẽ xử lý
// connectPeer(192.168.126.100,7000)

void* receiveMessages(void* arg);
#endif
