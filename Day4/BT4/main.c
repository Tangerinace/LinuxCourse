#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


int arr[100];
int chan_count = 0;
int le_count = 0;


void random_array() {
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100 + 1;  
    }
}


void* count_chan(void* arg) {
    for (int i = 0; i < 100; i++) {
        if (arr[i] % 2 == 0) {
            chan_count++;
        }
    }
    return NULL;
}


void* count_le(void* arg) {
    for (int i = 0; i < 100; i++) {
        if (arr[i] % 2 != 0) {
            le_count++;
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));  

    random_array();

    pthread_t thread1, thread2;


    pthread_create(&thread1, NULL, count_chan, NULL);


    pthread_create(&thread2, NULL, count_le, NULL);

    // Đợi cho đến khi cả hai thread hoàn thành
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // In kết quả
    printf("Tổng số số chẵn: %d\n", chan_count);
    printf("Tổng số số lẻ: %d\n", le_count);

    return 0;
}
