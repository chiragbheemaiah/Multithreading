#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

// Barriers only allows threads to pass through once only a suffcient number of threads are accumulated.
// if threads reach a certain point by taking different times and we need them to be synced up we can use barriers.
// Useful for synchronizing threads.
pthread_barrier_t barrier;

void* routine(void* arg){
    int sleepDuration = rand() % 5 + 1;
    sleep(sleepDuration);
    printf("Waiting at barrier - Thread - %d!, slept for %d\n", *(int*)arg, sleepDuration);
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier! - Thread - %d\n", *(int*)arg);
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    int numberOfThreads = 5;
    int barrierCount = 3;
    pthread_t th[5];
    pthread_barrier_init(&barrier, NULL, barrierCount);
    for(int i = 0; i < numberOfThreads; i += 1){
        int *threadNumber = malloc(sizeof(int));
        *threadNumber = i;
        if(pthread_create(&th[i], NULL, &routine, (void*)threadNumber)){
            return -1;
        }
    }
    for(int i = 0; i < numberOfThreads; i += 1){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    pthread_barrier_destroy(&barrier);

    return 0;
}