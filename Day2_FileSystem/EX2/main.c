#include <stdio.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 

int main(int argc, char*argv[] ){
    if( argc != 5){
        printf("The number of arguments must be 5\n");
        return 1;
    }

    const char*ex_file = argv[1];
    int number = atoi(argv[2]); 
    char mode = argv [3] [0]; 
    const char*data = argv[4];

    int fd;
    if(mode == 'r') { 
        fd = open(ex_file,O_RDONLY); 
        if(fd == -1) {
            printf("Cannot open the file for reading\n");
            return 1;
    }

    char docfile[number + 1]; 
    int readbyte = read(fd,docfile,number); 
    if(readbyte == -1) {
        printf("Failed to read from file\n");
        close(fd);
        return 1;
    }
    docfile[readbyte] = '\0'; 
    printf("Data from the file: %s\n",docfile); 
    close(fd);

    }
    else if (mode  == 'w') {
        fd = open(ex_file,O_WRONLY|O_CREAT|O_APPEND,0666);
        if(fd == -1) {
            printf("Cannot open the file for writing\n");
            return 1;
        }

int writebyte = write(fd,data, number);
    if(writebyte == -1) {
        printf("Can't write into the file\n");
        close(fd);
        return 1; 
        }

    fsync(fd);
    printf(" Wrote %d byte into the file\n",writebyte);
    close(fd);
    }

    else {
        printf("Invalid mode.Only use 'r' or 'w'\n");
        return 1;
        }

    return 0;
    
}
