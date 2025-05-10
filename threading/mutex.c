#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

// // Threads share:
// 1. Heap memory
// 2. Global variables
// 3. Resources
// 4. File Descriptors
// 5. Code Section
// 6. Address Space

// // Threads DO NOT share
// 1. Local variables
// 2. CPU registers and PC


    // Race Condition:
    // 1. Read the value
    // 2. Increment the value
    // 3. Write the value to memory

    // Init value: 23
    // If t1 and t2 both read in the value to their registers at the same time. 
    // After this t1 receives a large chunk of the CPU and increments
    // the value to 30 and writes it to memory.

    // Now t2 gets the CPU and continues executing from its register having 23.
    // The CPU increments this value and return it to the register
    // After which the value is written to memory -> 24



// Mutex - Lock around a section ofcode that is critical
pthread_mutex_t mutex;
int mails = 0;
// int lock = 0;
void* routine(){
    for(int i=0; i<100000; i++){
        // while (lock == 1){
        //     continue;
        // }
        // lock = 1;
        pthread_mutex_lock(&mutex);
        mails += 1;
        pthread_mutex_unlock(&mutex);

        // lock = 0;

    }

}

int main(int argc, char* argv[]){
    // pthread_t t1, t2;
    // pthread_mutex_init(&mutex, NULL);
    // if(pthread_create(&t1, NULL, &routine, NULL) != 0){
    //     return 1;
    // }
    // if(pthread_create(&t2, NULL, &routine, NULL) != 0){
    //     return 2;
    // }
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);

    // printf("Total number of mails: %d\n", mails); // Total number of mails: 117993
    // pthread_mutex_destroy(&mutex);

    pthread_mutex_init(&mutex, NULL);
    pthread_t th[8];
    for(int i=0;i<8;i++){
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0){
            return -1;
        }
    }
    for(int i=0; i < 8; i++){
        if(pthread_join(th[i], NULL) != 0){
            return -2;
        }
    }
    pthread_mutex_destroy(&mutex);
    printf("Mails: %d \n", mails);
    return 0;
}