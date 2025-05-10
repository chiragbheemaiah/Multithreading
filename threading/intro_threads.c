#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

// Function to run on a thread
void* routine(){
    printf("Testing from threads\n");
    sleep(5);
    printf("Ending execution\n");
}


int main(int argc, char* argv[]){
    pthread_t t1;
    pthread_t t2;
    if(pthread_create(&t1, NULL, &routine, NULL) != 0){ //signature -> (pthread_t variable, settings [NULL -> default], function, function_parameters)
        return -1;
    }
    if(pthread_create(&t2, NULL, &routine, NULL) != 0){
        return -1;
    }
    
    
        // we require the process to wait for the thread to complete execution before exiting
    pthread_join(t1, NULL); // wait till thread completes execution. Signature (thread, pointer to get return value from  function)
    pthread_join(t2, NULL);
    return 0;
}