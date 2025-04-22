
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    pid_t pid = fork();
    int status;
    pid = fork();

    if (pid == -1){
        printf("Khong tao được tiến trình con");
        return 1;

    }
    else if(pid == 0){
        printf(" tien tinh con dang chay voi PID la %d\n",getpid());
        exit(5);
    
    }
    else {
        wait(&status);
        if(WEXITSTATUS(status)){
            int code = WEXITSTATUS(status);
            printf("tien trinh con ket thuc voi ma %d\n",code);

        }
        else{
            printf(" tien trinh con ket thuc khong dung cach\n");

        }
    }
    return 0;
}