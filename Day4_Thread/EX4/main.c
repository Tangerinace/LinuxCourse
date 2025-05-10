#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int arr[2000];
int evenCount = 0;
int oddCount = 0;

void random_array()
{
    for(int i = 0; i<100; i++){
        arr[i] = rand() %100 + 1;       
    }
}


void* even_count(void* arg){
    for(int i = 0; i< 100; i++){
        if(arr[i] % 2 == 0){
            evenCount++;
        }
    }

    return NULL;
}

void* odd_count(void* arg){
    for(int i = 0; i< 100; i++){
        if(arr[i] % 2 != 0){
            oddCount++;
        }
    }
        
    return NULL;
}

int main(){
    srand(time(NULL));
    random_array();
    pthread_t thread1,thread2;

    pthread_create(&thread1, NULL, even_count, NULL);
    pthread_create(&thread2, NULL, odd_count, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Sum of even number: %d\n", evenCount);
    printf("Sum of odd number: %d\n", oddCount);
    
    return 0;
}
