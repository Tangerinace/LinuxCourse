// tiến trình Zombie
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    pid_t pid =fork();
     if (pid == -1){
        printf(" Lỗi khi tạo tiến trình con");
        return 1;

     }
     if(pid == 0){
        printf(" tiến trình con kết thúc với PID : %d\n",getpid());
        exit(0);

     }
     else{
        printf(" Tiến trình cha với PID: %d đang dần biến mất để tạo zombie \n",getpid());
        sleep(15); //lúc này sẽ xuất hiện tiến trình Zombie
    printf(" tiến trình cha xuất hiện trở lại\n");
    }
return 0;
}
