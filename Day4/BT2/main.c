#include <stdio.h>
#include <pthread.h>


int counter = 0;

pthread_mutex_t lock;

void* counter_tang(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
       
    }
    return NULL;

}

int main(){
    pthread_t t1,t2,t3;

    pthread_mutex_init(&lock,NULL);
    
    pthread_create(&t1,NULL, counter_tang,NULL);
    pthread_create(&t2,NULL, counter_tang,NULL);
    pthread_create(&t3,NULL, counter_tang,NULL);


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);


  
    printf("Thread dang chay: counter = %d\n", counter);  // <<== Thêm dòng này

    pthread_mutex_destroy(&lock);
    return 0;

}