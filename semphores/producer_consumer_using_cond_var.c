#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

#define BUFFER_SIZE 10
#define NUM_OF_THREADS 10

//PRODUCER-CONSUMER PROBLEM
// 1. IMAGINE A  SHARED BUFFER BETWEEN THREADS, THATIS ACCESSED BY PRODUCERS TO PUT SOME DATA INTO THE BUFFER.
// 2. THE CONSUMER THEN READS FROM THIS BUFFER, AS THE DATA IS AVAILABLE.

// EXAMPLE: PRINTER QUEUE. 10 PPL EANT TO USE THE PRINTER. QUEUE THE REQUESTS IN THE ORDER OF ARRIVAL AND PROCESS IT.

// PROBLEMS:
// AVOID RACE CONDITION
// WHAT HAPPENS IF THE BUFFER IS FULL IF THE PRODUCER IS TOO FAST
// IF THE BUFFER IS EMPTY DUE TO CONSUMER BEING TOO FAST


int buffer[BUFFER_SIZE];
int bufferCnt = 0;

pthread_mutex_t mutex;
pthread_cond_t condprodMutex, condConsMutex;

void* producer(void* arg){ 
    while(1){
        int x = rand() % 10 + 1;
        sleep(1);
        pthread_mutex_lock(&mutex);
        while(bufferCnt >= BUFFER_SIZE){
            pthread_cond_wait(&condConsMutex, &mutex);
            // sleep(1);
        }
        buffer[bufferCnt] = x;
        bufferCnt += 1;
        printf("Produced: %d\n", x);
        // cond_broadcast
        pthread_cond_broadcast(&condprodMutex);
        // printf("Skipped data!\n");
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* consumer(void* arg){
    int y = -1;
    while(1){
        pthread_mutex_lock(&mutex);
        while(bufferCnt == 0){
            // sleep(1);
            pthread_cond_wait(&condprodMutex, &mutex);
        }
        y = buffer[bufferCnt - 1];
        bufferCnt -= 1;
        pthread_cond_signal(&condConsMutex);

        pthread_mutex_unlock(&mutex);
        
        printf("Received value is %d\n", y);
        sleep(2);
    }
}


int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[NUM_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condprodMutex, NULL);
    pthread_cond_init(&condConsMutex, NULL);
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(i % 2 == 0){
            if(pthread_create(&th[i], NULL, &producer, NULL)){
                return -1;
            }
        }
        else{
            if(pthread_create(&th[i], NULL, &consumer, NULL)){
                return -1;
            }
        }
    }
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condprodMutex);
    pthread_cond_destroy(&condConsMutex);

    return 0;
}
