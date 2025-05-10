#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// Communication between processes are carried out by an in memory file called as the PIPE
// bith read and write are blocking!
int main(int argc, char* argv[]){
    int fd[2];
    // fd[0] -> read end, fd[1] -> write end
    if(pipe(fd) == -1){//signature -> (key for a file descriptor), requires two fd
        printf("An error occured with opening pipe!");
        return -1;
    }
    int id = fork(); // the process each have independent file descriptors inherited
    if(id == 0){
        close(fd[0]);
        int x;
        printf("input a number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1){
            return -1;
        }
        close(fd[1]);
    }else{
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            return -1;
        }
        close(fd[0]);
        printf("Received from child process: %d", y);
    }

    return 0;
}