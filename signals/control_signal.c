#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == 0){
        while(1){
            printf("Doing something!\n");
            sleep(1);
            // fflush(stdout);
        }
    }else{
        sleep(5);
        kill(pid, SIGSTOP);
        printf("Waiting in main process\n");
        sleep(2);
        kill(pid, SIGCONT);
        sleep(5);
        kill(pid, SIGKILL);
        wait(NULL);
        printf("Child is killed!\n");
    }
    return 0;
}