#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 
#include <signal.h> 

void sigusr1(int signum){ 
    printf(" Child Process has been received signal from Parent Process\n");
}

int main(){
    pid_t chilPid = fork();
    if(chilPid == -1) {
        printf("Failed to create Child Process\n");
        return 1;
    }

    else if(chilPid == 0 ) {
        signal(SIGUSR1,sigusr1);  
        printf(" Wait signal sent from Parent Process\n");
        pause(); 
        printf("Child Process has been received from Parent Process and have PID: %d\n",getpid());
        exit(0);
    }

    else {
        sleep(2); 
        if(kill(chilPid, SIGUSR1) == -1) { 
        printf("Failed to sended signal from SIGUSR1\n");
        return 1;
    }
    
        wait(NULL); 
        printf("Parent Process has been sent signal to Child Process and have PID: %d\n",getpid());
    }

    return 0;
}
    

