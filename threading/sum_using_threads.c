#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int array[] = {1,1,1,1,1,2,2,2,2,2};

void* routine(void* arg){
    int end = *(int*)arg;
    int sum = 0;
    for(int i= end-5;i<end;i++){
        sum += array[i];
    }
    *(int*)arg  = sum;
    return (void*)arg;
}


int main(int argc, char* argv []){
    pthread_t th[2];
    for(int i = 0; i < 2 ; i++){
        int *end = malloc(sizeof(int));
        *end = (i+1)*5;
        pthread_create(&th[i], NULL, &routine, (void*)end);
    }
    int *res;
    int globalSum = 0;
    for(int i=0;i<2;i++){
        pthread_join(th[i], (void**)&res);
        globalSum += *res;
    }
    printf("Total sum is : %d\n", globalSum);
    free(res);
    return 0;
}
