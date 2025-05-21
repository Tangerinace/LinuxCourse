#ifndef SERVER_H // nếu chưa định nghĩa
#define SERVER_H // nếu chưa định nghĩa thì định nghĩa luôn

int startServer(int port); // hàm khởi động server(tạo TCP socket, gắn socket vào địa chỉ IP)
//port là chỉ peer sẽ lắng nghe
void* serverListener(void* arg); // dùng như là 1 thread function

int getListenport();// là 1 hàm để lấy lại số port server đang dùng để kết nối các máy khác

#endif //kết thúc vùng kiểm tra


