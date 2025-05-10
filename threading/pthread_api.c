#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// SETUP: FUEL STATION GETS FILLED BY A THREAD. 
// A CAR TAKES FUEL FROM STATION BY AOTHER THREAD

// COND FUNCTIONALITY:
// 1. WAIT
// 2. BROADCAST
// 3. SIGNAL

// pthread_cond_wait() will wait for a signal from another thread to resume its operation!
int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t condFuel;

void* fuel_filling(void* arg){
    for(int i=0;i<15;i++){
        pthread_mutex_lock(&fuel_mutex);
        fuel += 15;
        printf("Filled fuel .. %d!\n", fuel);
        // pthread_cond_signal(&condFuel);
        pthread_cond_broadcast(&condFuel);

        pthread_mutex_unlock(&fuel_mutex);
        sleep(1);
    }
}

void* car_filling(void* arg){
    // Here we lock the function until fuel is available.
    int* carNumber = (int*)arg;
    pthread_mutex_lock(&fuel_mutex);
    while(fuel - 40 < 0){
        printf("Not enough fuel left! Waiting! - %d\n", *carNumber);
        // sleep(1);

        // This essentially:
        // 1. unlocks the mutex
        // 2. wait for a signal
        // 3. lock the mutex when the signal is received
        pthread_cond_wait(&condFuel, &fuel_mutex); 

    }
    fuel -= 40;
    pthread_mutex_unlock(&fuel_mutex);
    printf("Got fuel, now left: %d!\n", fuel);
    free(carNumber);



}
// CONDITION VARIABLES

int main(int argc, char* argv[]){
    pthread_t th[5];
    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&condFuel, NULL);
    for(int i=0;i<5;i++){
        if(i == 1){
            if(pthread_create(&th[i], NULL, &fuel_filling, NULL)){
                return -1;
            }
        }else{
            int *carNumber = malloc(sizeof(int));
            *carNumber = i;
            if(pthread_create(&th[i], NULL, &car_filling, (void*)carNumber)){
                return -2;
            }
        }
    }
    for(int i=0;i<5;i++){
        if(pthread_join(th[i], NULL)){
            return -3;
        }
    }
    pthread_mutex_destroy(&fuel_mutex);
    pthread_cond_destroy(&condFuel);

    return 0;
}