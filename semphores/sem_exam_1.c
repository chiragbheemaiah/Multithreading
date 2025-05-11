#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<semaphore.h>

#define NUM_OF_THREADS 10

// APPLICATION: LOGIN QUEUE
// Allows only 12 people to login at a time.


// Difference between semaphore and mutex
// Semaphore:

//     Not owned by a thread. Any thread can sem_post() even if it didn’t sem_wait().

//     Good for signaling between threads.

// Mutex:

//     Owned by the locking thread.

//     Only the thread that locked it can unlock it.


sem_t semaphore;                

void* routine(void* arg){
    printf("Waiting in the lobby! - Player %d\n", *(int*)arg);
    sem_wait(&semaphore);
    printf("Entered the game!- Player %d\n", *(int*)arg);
    sleep(30);
    printf("Game over!\n");

    // printf("Threading in progress from thread %d\n", *(int*)arg); //critical section
    sem_post(&semaphore);

    // printf("Completed!\n");
    free(arg);
}

int main(int argc, char* argv[]){
    pthread_t th[NUM_OF_THREADS];
    sem_init(&semaphore, 0, 3); //the second parameter is to denote if multiple processes are being used - pass 1
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