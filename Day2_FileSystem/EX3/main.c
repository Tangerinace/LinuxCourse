#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <time.h> 

int main(){
    const char*filename = "hello.txt" ;
    const char*data = " Kamen rider Decade" ;

    int fd;
    fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(fd == -1) {
        printf("Failed to open the file");
        return 1;
    }
    
    write(fd,data,strlen(data)); 
    close(fd);

    struct stat file_infor;
    if(stat(filename, &file_infor ) == -1) { 
        printf("Failed to get data from the file");
        return 1;
    }

    printf("FileName : %s\n",filename);

    if(S_ISREG(file_infor.st_mode)) { 
        printf("This is regular file\n");
    }

    else if(S_ISDIR(file_infor.st_mode)) {
        printf("This is directory file\n");
    } else {
        printf(" Other file type\n");
    }

    printf(" Last modification time %s\n",ctime(&file_infor.st_mtime));
    printf(" file size %ld byte\n",file_infor.st_size); 
    

    return 0;
}
