#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define NUM_OF_THREADS 4

pthread_mutex_t fuelMutex, waterMutex;
int fuel = 0;
void* routine(void* arg){
    pthread_mutex_lock(&fuelMutex);
    fuel += 50;
    pthread_mutex_unlock(&fuelMutex);
    printf("Fuel incremented to %d\n", fuel);
}

// 🔁 Conditions for Deadlock (Coffman conditions):

//     Mutual Exclusion — A resource can be held by only one thread.

//     Hold and Wait — A thread holding a resource is waiting for another.

//     No Preemption — Resources can't be forcibly taken away.

//     Circular Wait — A circular chain of threads exists, each waiting for a resource held by the next.

// If all four conditions hold, deadlock can occur.



// //  DEADLOCK SCENARIO 1: CALLING LOCK TWICE IN THE SAME THREAD!

// void* routine(void* arg){
//     pthread_mutex_lock(&fuelMutex);
//     pthread_mutex_lock(&fuelMutex);
//     fuel += 50;
//     pthread_mutex_unlock(&fuelMutex);
//     pthread_mutex_unlock(&fuelMutex);
//     printf("Fuel incremented to %d\n", fuel);
// }

// DEADLOCK SCENARIO TWO: CYCLIC ORDER OF CALLING LOCKS

// void* routine(void* arg){
//     if(rand() % 2 == 0){
//         pthread_mutex_lock(&fuelMutex);
//         sleep(1);
//         pthread_mutex_lock(&waterMutex);
//     }else{
//         pthread_mutex_lock(&waterMutex);
//         sleep(1);
//         pthread_mutex_lock(&fuelMutex);
//     }

//     printf("Locks Acquired!\n");
//     sleep(5);

//     pthread_mutex_unlock(&fuelMutex);
//     pthread_mutex_unlock(&waterMutex);

// }

int main(int argc, char* argv[]){

    pthread_t th[NUM_OF_THREADS];
    pthread_mutex_init(&waterMutex, NULL);
    pthread_mutex_init(&fuelMutex, NULL);
    // The second argument of pthread_mutex_init() is used too define the type of mutex.
    // A special type of mutex called the RECURSIVE MUTEX allows a thread to lock a resource several times. 
    // However, it must also unlock it equal number of times for it to be considered unlocked for other threads.

    // To set a mutex as recursive the following must be specified.

    // pthread_mutexattr_t recursiveMutexAttr;
    // pthread_mutexattr_init(&recursiveMutexAttr);
    // pthread_mutexattr_settype(&recursiveMutexAttr, PTHREAD_MUTEX_RECURSIVE);
    // pthread_mutex_init(&fuelMutex, &recursiveMutexAttr);
    // pthread_mutexattr_destroy(&recursiveMutexAttr);

    for(int i=0;i<NUM_OF_THREADS;i++){
        if(pthread_create(&th[i], NULL, &routine, NULL)){
            return -1;
        }
    }
    for(int i=0;i<NUM_OF_THREADS;i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    pthread_mutex_destroy(&fuelMutex);
    pthread_mutex_destroy(&waterMutex);
    printf("Fuel Total %d\n", fuel);

    return 0;
}