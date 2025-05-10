#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

// TASK: If the user does not respond for some time prompt him again
void handlesigusr1(int sig){
    printf("Hello???? You there?\n");
}

int x = -1;

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        return -1;
    }
    if(pid == 0){
        while(x == -1){
            sleep(5);
            kill(getppid(), SIGUSR1);
        }

    }else{
        struct sigaction sa = {0};
        sa.sa_handler = &handlesigusr1;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the result of 5x3?: \n");
        scanf("%d", &x);
        if(x == 15){
            printf("Correct\n");
        }else{
            printf("Wrong!\n");
        }
        wait(NULL);
    }
    return 0;
}