#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {


    int fd;
    const char*data = "AAAAAA\n";

    fd = open("hello.txt", O_WRONLY | O_APPEND |O_CREAT,0666);
    if(fd == -1){
        printf("Không thể mở file\n");
        return 1;
    }
    if(lseek(fd,0, SEEK_SET) == -1){
        printf("Lỗi khi Seek về đầu file\n");
        close(fd);
        return 1;
    }
    if(write(fd, data, 6) == -1){
        printf("Error");
        close(fd);
        return 1;

    }
   

    printf(" đã ghi dữ liệu vào file\n");
    
    

    close(fd);
    return 0;
}

//Khi chạy thì chuỗi kí tự trên sẽ in ở vị trí cuối của file bởi vì hàm O_APPEND sẽ luôn đảm bảo dữ liệu được write() sẽ ở cuối file
// không quan tâm con trỏ đặt ở đâu dù đã seek về đầu file