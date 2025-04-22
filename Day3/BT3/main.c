
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void sigusr1(int signum) {
    printf("tiến trình con đã nhận được tín hiệu SIGUSR1 từ papa \n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("fork fail");
        return 1;
    }

    if (pid == 0) {
        
    
        signal(SIGUSR1, sigusr1); 

        printf("wait for signal from parent process\n");
        pause();  
        printf("thực hiện việc nhận signal\n");
    } else {
        
        sleep(2);  
        kill(pid, SIGUSR1);  
        wait(NULL); 
        printf("đã gửi tín hiệu đến tiến trình con\n");
    }

    return 0;
}
