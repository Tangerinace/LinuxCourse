

#include <stdio.h>
#include <pthread.h>

void*threadfunction(void*arg){
    int id = *(int*)arg;
    printf("Thread so %d: Hello from Thread\n",id);
    pthread_exit(NULL);
}
int main(){
    pthread_t thread1,thread2;
    int id1 = 1, id2 =2;

    pthread_create(&thread1,NULL,threadfunction,&id1);

    pthread_create(&thread2,NULL,threadfunction,&id2);


    pthread_join(thread1,NULL);

    pthread_join(thread2,NULL);

    printf(" Tất cả Thread đã được tạo hoàn thành\n");

    return 0;
}