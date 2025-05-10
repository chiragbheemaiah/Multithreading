#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
// Process implementation

int main(int argc, char* argv[]){
    int x = 2;
    int pid = fork();
    if(pid == 0){
        // child process
        x += 1;
        printf("%d\n", x);
    }
    printf("Hello from processes\n");
    printf("Process ID: %d\n", getpid());
    if(pid != 0){
        // parent process
        wait(NULL);
        printf("%d\n", x);
    }
}