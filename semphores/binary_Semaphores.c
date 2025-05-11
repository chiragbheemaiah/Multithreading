#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int *fuel;
sem_t binary_sem;

// BINARY SEMAPHORES CAN BE USED LIKE MUTEXES. 
// ADDITIONALLY THEY CAN BE USED TO NOTIFY OTHER THREADS THAT A THREAD HAS FINISHED EXECUTING WHATEVER IS NEEDED.


// DIFFERENCE BETWEEN SEMAPHORE AND MUTEX
// 1. MUTEX ABIDE BY OWNERSHIP THAT IS A THREAD WHICH LOCKS MUST UNLOCK IT.
// 2. SEMAPHORE DOES NOT FOLLOW OWNERSHIP CAN BE WAIT AND POST IN DIFFERNT THREADS AND IN ANY ORDER.
void* routine(void* arg){
    // Perform some task
    printf("Filling fuel in the tank\n");
    *fuel += 50;
    sleep(5);
    sem_post(&binary_sem);
}

int main(int argc, char* argv[]){
    pthread_t th;
    sem_init(&binary_sem, 0, 0);
    fuel = malloc(sizeof(int));
    *fuel = 0;
    pthread_create(&th, NULL, &routine, NULL);

    // wait for the update to be done
    sem_wait(&binary_sem);
    free(fuel);
    printf("Destroyed fuel in the tank!\n");


    pthread_join(th, NULL);
    sem_destroy(&binary_sem);
    return 0;
}