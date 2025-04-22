
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main(){

    pid_t pid = fork();

    if(pid == -1){
        printf(" Loi lkhi tao tien trinh con\n");
        return 1;
    }
    if(pid ==0){
        char*action =getenv("ACTION");
        if(action == NULL){
            printf("chua thiet lap bien moi truong \n");
            exit(1);
        }
        if(strcmp(action,"1")==0){
            execlp("ls","ls","-l",NULL);
        }
        else if(strcmp(action,"2")==0){
            execlp("date","date",NULL);

        }else{
            printf(" gia tri k lop he yeu cau dung'1' hoac '2'\n");

        }
        printf("exec fail");
        exit(1);

    }else{
        wait(NULL);
        printf(" tien trinh con da ket thuc");

    }
    return 0;
}



