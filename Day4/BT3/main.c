#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>  


int data = 0;
pthread_mutex_t mutex; 
pthread_cond_t cond;   



void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {

        data = rand() % 10 + 1;  
        printf("Producer: Tạo số %d\n", data);


        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond); 
        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
    return NULL;
}


void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);


        pthread_cond_wait(&cond, &mutex);
        

        printf("Consumer: Đọc số %d\n", data);

        pthread_mutex_unlock(&mutex);

        sleep(1); 
    }
    return NULL;
}

int main() {
    srand(time(NULL));  

    pthread_t t1, t2;


    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);


    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

