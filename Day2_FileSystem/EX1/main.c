#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <string.h> 

int main(){
    int fd; 
    const char*data_write = "Decade\n"; 

    fd = open("hello.txt" ,O_CREAT| O_WRONLY| O_APPEND,0666); 


    if(fd == -1){
        printf("Can't open the file!!");
        return 1;
    }
    if(lseek(fd,0,SEEK_SET) == -1){
        printf("Can't move to begin of the file");
        close(fd);
        return 1;
    }
    if(write(fd,data_write,6) == -1){
        printf(" Can't write in the file");
        close(fd); 
        return 1;
    }

    printf("Write success in the file");
    close(fd);
    return 0;
}