#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

// threads implementation


// Forking creates new proceess and duplicates the memory, file handlers of the parent process into child process.
// Threads share the variables, file handlers, resources across several threads

int x = 2;

void* routine(){
    printf("Hello from threads\n");
    printf("Process ID: %d\n", getpid());
    sleep(2);
    printf("Hello from threads\n");
}

void* routine1(){
    x += 1;
    sleep(2);
    printf("value of x: %d\n", x);
}

void* routine2(){
    sleep(2);
    printf("value of x: %d\n", x);
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &routine1, NULL);
    pthread_create(&t2, NULL, &routine2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}