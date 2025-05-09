#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t childPid = fork();
    if(childPid == -1) {
        printf("Failed to create Child Process ");
        return 1;
    }

    if(childPid == 0) {
        sleep(15);
        printf("PID Child Process: %d &Because it doesnt have Parent Process so it is Orphan Process\n", getpid());
        exit(0);
    }

    else {
        printf("Parent Process terminated immediately and has PID: %d\n",getpid());
        exit(0);
    }
    return 0;

}

