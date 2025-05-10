#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
    int id = fork();
    // printf("Current ID: %d, Parent ID: %d\n", getpid(), getppid());
    // Current ID: 51452, Parent ID: 5974
    // Current ID: 51453, Parent ID: 51452


    // Wait the child and finish the parent
    if(id == 0){
        sleep(5);
    }
    printf("Current ID: %d, Parent ID: %d\n", getpid(), getppid());
    // When the child executes its parent is dead, therefore the system assigns it a new parent process. (2047)
    // Leads to memory leak
    // Solved by calling wait(NULL)
    int res = wait(NULL)
    if(res == -1){
        printf("no child to wait for\n");
    }else{
        printf("Finished execution\n")
    }
    return 0;
}