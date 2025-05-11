#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>

#define NUM_OF_THREADS 4


// Semaphore support two operations
// 1. wait ~ lock
// 2. post ~ unlock

sem_t semaphore;

//  SEMAPHORES: 
// 1. sem_wait -> s -= 1, if(s == 0), then wait on it
// 2. sem_post -> s += 1
// The value of the semaphore determines how many threads can simultaneously access the critical section
                

void* routine(void* arg){
    sem_wait(&semaphore);
    sleep(1);
    printf("Threading in progress from thread %d\n", *(int*)arg); //critical section
    sem_post(&semaphore);

    // printf("Completed!\n");
    free(arg);
}

int main(int argc, char* argv[]){
    pthread_t th[NUM_OF_THREADS];
    sem_init(&semaphore, 0, 1); //the second parameter is to denote if multiple processes are being used - pass 1
                                // the third parameter is the value of the semaphore.
    for(int i=0;i<NUM_OF_THREADS;i++){
        int *idx = malloc(sizeof(int));
        *idx = i;
        if(pthread_create(&th[i], NULL, &routine, (void*)idx)){
            return -1;
        }
    }
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    sem_destroy(&semaphore);
    return 0;
}