#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid =fork();


    if(pid == -1){
        printf(" Lỗi tạo tién trình con \n");
        return 1;

    }
        else if(pid ==0){
            printf(" Đây là tiến trình con PID là %d\n",getpid());

        }
        else{
            printf(" đây là tiến trình cha %d\n",getpid());
        }

        return 0;
}


