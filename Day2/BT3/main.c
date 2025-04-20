#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>


int main(){
    const char*filename = "hello.txt";
    const char*data = "Xin chao day la Linux";


    int fd;
    fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC,0666 );
    if (fd ==-1){
        printf("Khong the mo file");
        return 1;

    }
    write(fd, data,strlen(data));
    close(fd);
    struct stat infor;
    if(stat(filename, &infor) == -1)
    {
       printf(" khong the lay thong tin");
       return 1;

    }
    printf("Ten file: %s\n",filename);


    if((infor.st_mode)){
        printf(" Day la regular file\n");
    }
    else if(S_ISDIR(infor.st_mode)){
        printf(" Day la file thu muc\n");

    }
    else
        printf("file khac\n");

        printf("Thoi gian chinh sua lan cuoi %s\n",ctime(&infor.st_mtime));

        printf(" kich thuoc file la %ld byte\n",infor.st_size);
        

        return 0;
    

}