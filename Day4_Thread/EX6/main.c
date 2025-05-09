#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define array_size 1000000
#define num_threads 4

int arr[array_size];
long long total_sum = 0; // in Linux just use long long because have 64bit
pthread_mutex_t lock;

void* sum_part(void* arg){
    int thread_id = *((int*)arg);
    int start = thread_id* (array_size/num_threads);
    int end = (thread_id + 1 )*(array_size/num_threads);

    long long part_sum  = 0;
    for(int i = start; i < end; i++){
        part_sum += arr[i];
    }

pthread_mutex_lock(&lock);
total_sum += part_sum;
pthread_mutex_unlock(&lock);

return NULL;
}

int main(){
    for(int i = 0; i < array_size; i++){
        arr[i] = rand() %100;
    }

    pthread_mutex_init(&lock, NULL);
    pthread_t threads[num_threads];
    int threadID[num_threads];

    for(int i = 0; i < num_threads; i++ ){
        threadID[i] = i;
        pthread_create(&threads[i], NULL, sum_part, (void*)&threadID[i]);
    }

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Sum of array: %lld\n", total_sum);
    pthread_mutex_destroy(&lock);

    return 0;
}

