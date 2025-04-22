// tạo tiến trình Orphan( Naruto , Bruce Wayne)
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    pid_t pid = fork();
    if(pid == -1){
        printf(" tao tien trinh con fail");
        return 1;

    }
    if(pid == 0){
        sleep(15);
        printf("Child (PID: %d, Parent PID: %d) - tiến trình orphan!\n", getpid(), getppid());

        //getppid ở đây là kiểm tra xem có tiến trình cha hay không nếu không có thì sẽ cho là mồ côi
    }
    else{
        printf(" tiến trình cha kết thúc ngay lập tức : %d",getpid());
        exit(0);
    }
    return 0;

}
