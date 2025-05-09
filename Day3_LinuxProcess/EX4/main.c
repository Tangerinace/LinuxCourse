#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t childPid = fork();
    int status; 

    if(childPid == -1) {
        printf(" Lỗi khi tạo tiến trình\n");
        return 1;
    }

    else if(childPid == 0) {
        printf("PID Child Process: %d\n",getpid());
        sleep(1);  
        exit(42); 
    }

    else {
        printf("PID Parent Process %d\n",getpid());
        wait(&status);
        if(WEXITSTATUS(status)) {
            int code = WEXITSTATUS(status); 
            printf("Child Process has been terminated and has code: %d\n",code);
        }

        else if(WEXITSTATUS(status)) {
            printf("Child Process has terminated with signal: %d\n",WEXITSTATUS(status));
        }

        else {
            printf("Child Process has not terminated incorrect\n");
        }
    }
    
    return 0;
}
