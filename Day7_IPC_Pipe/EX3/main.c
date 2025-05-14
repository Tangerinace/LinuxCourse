#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

#define MSG_SIZE 200

char *msg = "Xin chao day la Linux";

static void func(int signum)
{
    wait(NULL);
    printf("Child process is termination");
}

int main(int argc, char const *argv[]){
    char in_buff[MSG_SIZE];
    int num_read = 0;
    int fds[2];
    pid_t child_pid;

    if(pipe(fds) <0){
        printf("pipe unsuccessfully\n");
        exit(1);
    }

    child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){
            printf(" I am child\n");

            while(1){
               num_read = read(fds[0],in_buff,sizeof(in_buff));
               if(num_read == -1){
                printf("Read failed");
                break;
               }
               else if(num_read == 0){
                printf("pipe end-of-pipe\n");
                break;
               }
               else{
                int length = strlen(in_buff);
                printf("Message: %s\n",in_buff);
                printf("Number of mes: %d\n",length);
               }
            };
        }else{
            signal(SIGCHLD,func);
            printf(" i am a parent\n");
            if(close(fds[0]) == -1)
                printf("close(fds[0]) failed");

            write(fds[1],msg,strlen(msg)+1);

            if(close(fds[1]) == -1)
                printf("close(fds[0]) failed\n");

            while(1);
        }
    }else{
        printf("fork() unsuccessfully");
    }
    return 0;
}