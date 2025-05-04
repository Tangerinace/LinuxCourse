#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define ARRAY_SIZE 1000000 
#define NUM_THREADS 4      


int arr[ARRAY_SIZE];        
long long total_sum = 0;    
pthread_mutex_t lock;       


void* sum_part(void* arg) {
    int thread_id = *((int*)arg);
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS);
    int end = (thread_id + 1) * (ARRAY_SIZE / NUM_THREADS);

    long long part_sum = 0;
    for (int i = start; i < end; i++) {
        part_sum += arr[i];
    }


    pthread_mutex_lock(&lock);
    total_sum += part_sum;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 100;  
    }


    pthread_mutex_init(&lock, NULL);

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];


    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_part, (void*)&thread_ids[i]);
    }


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }


    printf("Tổng của mảng là: %lld\n", total_sum);


    pthread_mutex_destroy(&lock);

    return 0;
}
