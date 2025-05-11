// WHAT ARE THREAD POOLS - WAY OF HANDLING SEVERAL TASKS IN A MULTITHREADED ENVIRONMENT
// PRESET NUMBER OF TASKS ARE ALWAYS EXECUTING IN A THREAD POOL
// TASKS ARE STORED IN FIFO QUEUE

// THE USER OR THE MAIN THREAD CREATES A NEW TASK ON QUEUE
// ASSIGN A THREAD TO A TASK
// EXECUTE THE TASK



#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

typedef struct Task{
    int a, b;
}Task;

#define NUM_OF_THREADS 16


pthread_mutex_t mutexQueue;
sem_t queue_full, queue_empty;

Task taskQueue[256];
int taskCnt = 0;

void executeTask(Task* task){
    int result = task->a + task->b;
    printf("Result: %d \n", result);
}

void* startThreads(void* args){
    while(1){
        // int found = 0;
        Task task;
        sem_wait(&queue_empty);
        pthread_mutex_lock(&mutexQueue);
        // if(taskCnt > 0){
        // found = 1;
        task = taskQueue[0];
        for(int i=1;i<taskCnt;i++){
            taskQueue[i-1] = taskQueue[i] ;
        }
        taskCnt-=1;
        // }
        pthread_mutex_unlock(&mutexQueue);
        executeTask(&task);
        sem_post(&queue_full);
        
        // execute task - outside the CS
        // if(found){
        // }
    }
}

void submitTask(Task* task){
    sem_wait(&queue_full);
    pthread_mutex_lock(&mutexQueue);
    taskQueue[taskCnt] = *task;
    taskCnt += 1;
    pthread_mutex_unlock(&mutexQueue);
    sem_post(&queue_empty);
}

int main(int argc, char* argv[]){
    sem_init(&queue_full, 0, 256);
    sem_init(&queue_empty, 0 , 0);
    pthread_mutex_init(&mutexQueue, NULL);
    srand(time(NULL));
    pthread_t th[NUM_OF_THREADS];
    for(int i =0;i<NUM_OF_THREADS;i++){
        if(pthread_create(&th[i], NULL, &startThreads, NULL)){
            return -1;
        }
    }

    for(int i=0; i<100; i++){
        int a = rand() % 10;
        int b = rand() % 10;
        Task t1;
        t1.a = a;
        t1.b = b;
        submitTask(&t1);
    }
    for(int i =0;i<NUM_OF_THREADS;i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    pthread_mutex_destroy(&mutexQueue);
    sem_destroy(&queue_full);
    sem_destroy(&queue_empty);

}