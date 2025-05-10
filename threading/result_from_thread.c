#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* routine(){
    int *p = malloc(sizeof(int));
    int a = 10;
    int b = 5;
    *p =  (a+b);
    return (void*)p;
}

int main(int argc, char* argv[]){
    pthread_t t1;
    if(pthread_create(&t1, NULL, &routine, NULL)){
        return -1;
    }
    int *res;
    if(pthread_join(t1, (void**)&res)){
        return -2;
    }
    printf("The sum is : %d" , **res);
    free(res);
    return 0;
}