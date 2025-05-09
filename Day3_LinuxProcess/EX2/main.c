#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <sys/types.h>
#include <string.h>


int main(){

    pid_t childPid = fork();

    if(childPid == -1) {
        printf("Failed to create Child Process\n");
        return 1; 
    }

    if(childPid == 0){
        char*action  = getenv("ACTION");
        if(action == NULL){ 
            printf("Environment variable has been not set \n");
            exit(1); 
        }

        if(strcmp(action,"1")==0) { 
            execlp("ls","ls","-l",NULL); 
        }

        else if(strcmp(action,"2")==0) { 
            execlp("date","date",NULL); 
        }

        else {
            printf("Invalid value, use '1' or '2'\n");
        }

        printf("exec fail");
        exit(1);
    } 

    else {
        wait(NULL); 
        printf("Child Process has terminated\n");
    }

    return 1;
}