#include <stdio.h>
#include <stdlib.h> // thư viện có exi
#include <unistd.h> // thư viện có hàm fork
#include <sys/wait.h>
// Tiến trình zombie là tiến trình con đã kết thúc (như exit(0)), nhưng cha chưa gọi wait để thu hồi trạng thái, nên nó chiếm một mục trong bảng tiến trình với trạng thái Z.

int main(){
    pid_t pid = fork();
    if(pid == -1){
        printf(" Lỗi khi tạo tiến trình con\n");
        return 1;
    }
    else if(pid == 0){
        printf(" tiến trình con được tạo với PID là %d",getpid());
        exit(0); //ép tiến trình con phải kết thúc ngay thì mới tạo ra tiến trình zombie
    }
    else{ //tiến trình cha
        printf(" tiến tình cha được tạo với PID là %d\n",getpid());
        sleep(60); // vẫn sẽ tạo tiến trình cha nhưng mà thay vì việc đọc tiến trình con luôn thì chúng ta sẽ để cho tiến trình cha ngủ 60s để cho tiến tình con không ai đọc và sẽ trở thành zombie
        
        printf(" tiến trình cha xuất hiện trở lại\n");

    }
    return 0;
}