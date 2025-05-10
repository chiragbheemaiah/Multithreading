#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(int argc, char* argv[]){
    int id = fork();
    int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
    if(file == -1){
        printf("Error while poening file!\n");
        return -1;
    }

    dup2(file, STDOUT_FILENO); //CLOSES EXISTING STREAM FOR STD_OUT AND POINTS IT OT THE DUPLICATED FD
    close(file);
    if(id == 0){
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL); //process id and fd which are already opened are not changed.
        if(err == -1){
            return -6;
        }
    }else{
        int wstatus;
        wait(&wstatus); // has information about child program execution
        if(WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0){
                printf("Success\n");
            }else{
                printf("Failure\n");
            }
        }
        printf("Some post processing goes here\n");
    }
    return 0;
}