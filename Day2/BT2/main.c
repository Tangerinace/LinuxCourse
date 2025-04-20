#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 


int main(int argc, char*argv[]){
    if(argc != 5){
        printf("Lỗi số arguments phải = 5");
        return 1;

    }

    const char *BT2 =  argv[1];
    int num_byte =  atoi(argv[2]); //atoi là hàm chuyển từ string sang số nguyên
    char mode = argv[3][0];
    const char *data = argv[4];
int fd;
    if(mode == 'r'){
        fd = open(BT2,O_RDONLY);
        if(fd == -1){
            printf("File khong dung de Read\n");
            return 1;


        }
    
char docfile[num_byte + 1];
int readbyte= read(fd, docfile, num_byte);
    if (readbyte == -1) {
        printf("Lỗi khi đọc file");
        close(fd);
        return 1;
    }

        docfile[readbyte] = '\0';
        printf(" Dữ liệu đọc từ file là : %s\n",docfile);
        close(fd);
    }

    else if (mode == 'w'){
        fd =open(BT2, O_WRONLY|O_CREAT,0666);
        if(fd ==-1){
            printf("File này không dùng để ghi\n");
            return 1;

        }
    int writebyte = write(fd, data, num_byte);
    if(writebyte ==-1){
        printf("file không ghi được\n");
        close(fd);
        return 1;

    }
    printf(" Ghi %d byte vào file \n", writebyte);
    close(fd);
    }
    else{
        printf(" không hợp lệ hãy sử dụng 'r' or 'w");
        return 1;

    }
    return 0;



}

// ./app hello.txt 5 r 0

// ./app hello.txt 7 w Rhyderrr
