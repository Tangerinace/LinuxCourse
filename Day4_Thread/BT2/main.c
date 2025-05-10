#include <stdio.h>
#include <pthread.h>

long counter = 0;
pthread_mutex_t lock;

void* counter_increase(void* arg){
    for(int i =0; i< 1000000;i++){
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    pthread_t threads[3];
    int threadID[3]= {1,2,3};
    pthread_mutex_init(&lock,NULL);

    for(int i = 0; i<3; i++){
        pthread_create(&threads[i], NULL, counter_increase, &threadID[i]);
    }

    for(int i = 0; i<3; i++){
        pthread_join(threads[i], NULL);
    }
    printf(" Final Result: %ld\n", counter);
    return 0;
}
