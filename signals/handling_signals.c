#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void handlesigtstp(int sig){
    printf("Stopping not allowed!");
}

void handlesigcont(int sig){
    // behaviour added not modified.
    printf("Enter input number: \n");
    fflush(stdout);
}

int main(int argc, char* argv[]){
    struct sigaction sa;
    // sa.sa_handler = &handlesigtstp;
    sa.sa_handler = &handlesigcont;
    sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL); //link signal to handler
    sigaction(SIGCONT, &sa, NULL); //link signal to handler


    int x;
    printf("Enter input number: ");
    scanf("%d", &x);
    printf("%d", x);
}