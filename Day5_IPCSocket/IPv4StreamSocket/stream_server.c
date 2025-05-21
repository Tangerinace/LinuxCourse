#include <stdio.h> //printf, perror
#include <stdlib.h> //exit, atoi, malloc
#include <string.h> //strcmnp
#include <errno.h> //prerro
#include <sys/socket.h>     //  Chứa cấu trúc cần thiết cho socket. 
#include <netinet/in.h>     //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h> // convert Binary ip to string
#include <unistd.h> //close, read, write, sleep
#include <asm-generic/socket.h> 

#define LISTEN_BACKLOG 50 // số lượng kết nối tối đa mà server có thể nhận
#define BUFF_SIZE 256 // size of cache
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0) // to handle error
//format do{....} while(0)

// chat function
void chat_func(int new_socket_fd) // hàm xử lý chat
{       
    int numb_read, numb_write; // Readbyte and writebyte
    char sendbuff[BUFF_SIZE]; // giới hạn số byte gửi
    char recvbuff[BUFF_SIZE]; // giới hạn số byte nhận
	
    while (1) {        
        memset(sendbuff, '0', BUFF_SIZE); // tạo vòng lặp để chat liên tục
        memset(recvbuff, '0', BUFF_SIZE); 

        /* Đọc dữ liệu từ socket */
        /* Hàm read sẽ block cho đến khi đọc được dữ liệu */
        numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);  //file, bộ đệm để lưu dữ liệu, byte tối đa
        if(numb_read == -1)
            handle_error("read()"); // read error exit program 

        if (strncmp("exit", recvbuff, 4) == 0) {  // check 4 byte đầu, nếu nhận là exit thì thoát chương trình
            system("clear");
            break; // thoát vòng lặp gần nhất ngay lập tức
        }

        printf("\nMessage from Client: %s\n", recvbuff);

        /* Nhập phản hồi từ bàn phím */
        printf("Please respond the message : ");
        fgets(sendbuff, BUFF_SIZE, stdin);  // đọc dữ liêuu buff_size từ bàn phím và lưu vào sendbuff

        /* Ghi dữ liệu tới client thông qua hàm write */
        numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff)); // sizeof(sendbuff) là vì so sách kích thước byte gửi
        if (numb_write == -1)
            handle_error("write()");
        
        if (strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        sleep(1); // tạm dừng 1 s để tiếp tục vòng lặp
    }
    close(new_socket_fd); //đóng vòng lặp 
}

int main(int argc, char *argv[]) //khai báo đối số
{
    int port_no, len, opt;  // number of port, size of client_addr, opt : select socket
    int server_fd, new_socket_fd;
    struct sockaddr_in serv_addr, client_addr; // sockaddr_in dùng trong giao tiếp mạng với IPv4
    //serv_addr: bind
    //client_addr: accept

    /* Đọc portnumber trên command line */
    if (argc < 2) { // 
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    } else
        port_no = atoi(argv[1]); // convert port to number save in port_no

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    
   //create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0); //make socket TCP IPv4
    if (server_fd == -1)
        handle_error("socket()");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        handle_error("setsockopt()");  

    /* Khởi tạo địa chỉ cho server */
    serv_addr.sin_family = AF_INET; // đặt loại địa chỉ IPV4
    serv_addr.sin_port = htons(port_no); // chuyển port sang định dạng mạng
    serv_addr.sin_addr.s_addr =  INADDR_ANY;// chấp nhận kết nối từ mọi địa chỉ IP //inet_addr("192.168.125.128"); //INADDR_ANY

    /* Gắn socket với địa chỉ server */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");
    //server_fd file descriptor
    //(struct sockaddr*)&serv_addr 
    // sizeof(serv_addr) kích thước cấu trúc địa chỉ

    if (listen(server_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen()"); 

    /* Dùng để lấy thông tin client */
	len = sizeof(client_addr);

    while (1) {
        printf("Server is listening at port : %d \n....\n",port_no);
		new_socket_fd  = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len); 
		if (new_socket_fd == -1)
            handle_error("accept()");

		system("clear"); // xoá màn hình nếu có kết nối mới
		
		//char temp[BUFF_SIZE];
		//inet_ntop(client_addr.sin_family, (struct sockaddr*)&client_addr, temp, sizeof(temp));
		printf("Server : got connection \n");
		        chat_func(new_socket_fd); // gọi hàm chat để xử lý
    }
    close(server_fd); // chạy xong thì đóng
    return 0;
}