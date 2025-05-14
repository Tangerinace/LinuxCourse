#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 16

char *msg1 = "Hello ,world 1";
char *msg2 = "Hello ,world 2";
char *msg3 = "Hello ,world 3";
char *msg4 = "Hello ,world 4";

static void func(int signum)
{
    wait(NULL);
    printf("Child process is termination\n");
}

int main(int argc, char const *argv[])
{
    char in_buff[MSG_SIZE];
    int num_read = 0;
    int fds[2];
    pid_t child_pid;

    if(pipe(fds) < 0){
        printf("pipe() unsuccessfully\n");
        exit(1);
    }
    child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){
            printf(" i am Child\n");

            while(1){
                num_read = read(fds[0],in_buff,MSG_SIZE);
                if(num_read == -1){
                    printf("read() failed\n");
                    exit(0);
                }

                else if(num_read == 0){
                    printf("pipe end-of-pipe\n");
                    break;
                }
            
                else{
                    printf("msg: %s\n",in_buff);
                }
            };

        }else{
                signal(SIGCHLD,func);
                
                printf(" i am a parent\n");
                if(close(fds[0]) == -1)
                    printf("close(fds[0]) failed");

                write(fds[1],msg1,MSG_SIZE);
                write(fds[1],msg2,MSG_SIZE);   
                write(fds[1],msg3,MSG_SIZE); 
                
                if(close(fds[1])== -1)
                    printf("close(fds[0]) failed\n");
                
                while(1);
            }
        } else {
            printf("fork() unsuccessfully");
        }
         return 0;
    }
   

