#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define NUM_OF_THREADS 8

int diceValues[NUM_OF_THREADS] = {0};
int status[NUM_OF_THREADS] = {0};

pthread_barrier_t diceRoll, setStatus;

void* routine(void* arg){
    int index = *(int*)arg; 
    diceValues[index] = rand() % 6 + 1;
    printf("Player %d rolled %d \n", index, diceValues[index]);

    pthread_barrier_wait(&diceRoll);
    pthread_barrier_wait(&setStatus);   

    if(status[index] == 1){
        printf("I won!  - Player %d \n", index);
    }else{
        printf("I lost!- Player %d \n", index);
    }

}
int main(int argc, char* argv[]){

    srand(time(NULL));
    pthread_t th[NUM_OF_THREADS];
    pthread_barrier_init(&diceRoll, NULL, NUM_OF_THREADS + 1);
    pthread_barrier_init(&setStatus, NULL, NUM_OF_THREADS + 1);
    for(int i=0; i<NUM_OF_THREADS; i++){
        int *idx = malloc(sizeof(int));
        *idx = i;
        if(pthread_create(&th[i], NULL, &routine, (void*)idx)){
            return -1;
        }
    }

    // main thread needs to wait before updating the status
    pthread_barrier_wait(&diceRoll);
    int max = 0;
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(diceValues[i] > max){
            max = diceValues[i];
        }
    }
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(diceValues[i] == max){
            status[i] = 1;
        }
    }
    pthread_barrier_wait(&setStatus);

    for(int i=0; i<NUM_OF_THREADS; i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    // for(int i=0;i<NUM_OF_THREADS;i++){
    //     printf("%d ", diceValues[i]);
    // }
    printf("\n");

    pthread_barrier_destroy(&diceRoll);
    pthread_barrier_destroy(&setStatus);
    return 0;
}