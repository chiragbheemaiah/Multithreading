#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include<semaphore.h>

#define BUFFER_SIZE 10
#define NUM_OF_THREADS 10

int buffer[BUFFER_SIZE];
int bufferCnt = 0;

pthread_mutex_t mutex;
sem_t sem_full, sem_empty;
void* producer(void* arg) {
    while (1) {
        int x = rand() % 10 + 1;
        sleep(1);
        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);
        buffer[bufferCnt] = x;
        bufferCnt++;
        printf("Produced: %d\n", x);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);
    }
}

void* consumer(void* arg) {
    int y = -1;
    while (1) {
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);
        y = buffer[bufferCnt - 1];
        bufferCnt--;
        printf("Consumed: %d\n", y);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);
        sleep(2);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    pthread_t th[NUM_OF_THREADS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem_empty, 0 , BUFFER_SIZE);
    sem_init(&sem_full, 0, 0);

    for (int i = 0; i < NUM_OF_THREADS; i++) {
        if (i % 2 == 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL)) {
                return -1;
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL)) {
                return -1;
            }
        }
    }

    for (int i = 0; i < NUM_OF_THREADS; i++) {
        if (pthread_join(th[i], NULL)) {
            return -2;
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_full);
    sem_destroy(&sem_empty);
    return 0;
}
