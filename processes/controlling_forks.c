// The child process copies the memory of the parent process after fork.


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
    int id = fork();
    // print 1 to 5 using child and 6 to 10 using parent
    int n;
    if(id == 0){
        n = 1;
    }
    else{
        n = 6;
    }
    // Ask the parent to wait till child is done
    if(id != 0){
        wait(NULL);
    }
    int i;
    for(i = n; i < n + 5; i++){
        printf("%d\n", i);
        fflush(stdout);
    }

    return 0;
}

// Output : Out of order numbers printed. OS decides the order of printing -> To Solve this we use a wait() function
// Wait() function asks the parent to wait for the child to finish.