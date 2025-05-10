#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int arr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// given an array of 10 elements, a thread should print a unique element from the array!
void* routine(void* arg){
    sleep(1);
    int* idx = (int*)arg;
    printf("%d ", arr[*idx]); //0 0 0 0 0 0 0 0 0 0 -> we are passing the referecce to a variable. This variable changes its value continously when i is changed.
    // when the process is executed after 1 second, the value of the emory location in 10, therefore all 0's are printed. 
    // instead we can send a dynamically allocated memory to each thread as arg.

    // Otherwise, we can send the memory address of the loaction in array.
}

int main(int argc, char* argv[]){
    int numOfThreads = 10;
    pthread_t th[numOfThreads];
    for(int i=0;i<numOfThreads;i++){
        // int *idx = &i;
        int *idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&th[i], NULL, &routine, (void*)idx);
    }
    for(int i=0;i<numOfThreads;i++){
        pthread_join(th[i], NULL);
    }
    return 0;
}