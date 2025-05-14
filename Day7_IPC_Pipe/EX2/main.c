#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>


#define BUF_SIZE 20


int main(){
    int fds1[2];
    int fds2[2];
    pid_t pid1,pid2;

    if(pipe(fds1) == -1 || pipe(fds2) == -1){
        printf(" Pipe error");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();

    if(pid1 == -1){
        printf("fork failed");
        exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        pid2 = fork();

        if(pid2 == -1){
            printf("fork failed");
            exit(EXIT_FAILURE);
        }

        if(pid2 ==0 ){
            close(fds1[0]);
            close(fds1[1]);
            
            close(fds2[1]);

            char buffer[BUF_SIZE];
            read(fds2[0],buffer,BUF_SIZE);
            printf("Process 2 child received message: %s\n",buffer);

            close(fds2[0]);
            exit(EXIT_FAILURE);
        }else{
            close(fds1[1]);
            close(fds2[0]);

            char buffer[BUF_SIZE];
            read(fds1[0],buffer, BUF_SIZE);

            strcat(buffer,"[modify by child 1]");
            write(fds2[1],buffer,strlen(buffer)+1);

            close(fds1[0]);
            close(fds2[1]);

            wait(NULL);
            exit(EXIT_SUCCESS);
        }
     } else{
            close(fds1[0]);
            close(fds2[0]);
            close(fds2[1]);

            char *msg = "hello";
            write(fds1[1], msg,strlen(msg)+1);

            close(fds1[1]);
            wait(NULL);

        }
          return 0;
    }
  




