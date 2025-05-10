#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv []){
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8};
    int fd[2];
    if(pipe(fd) == -1){
        printf("No water in the pipe!");
        return -1;
    }
    int id = fork();
    if(id == -1){
        printf("Suckks to be you!");
        return -1;
    }

    if(id == 0){
        int sum = 0;
        for(int i=0; i<4; i++){
            sum += arr[i];
        }
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1){
            printf("Error occured while writing sum from child!\n");
            return -1;
        }
        close(fd[1]);
    }else{
        int sum = 0;
        for(int i=4; i<8; i++){
            sum += arr[i];
        }
        int prev_sum = 0;
        close(fd[1]);
        if(read(fd[0], &prev_sum, sizeof(int)) == -1){
            printf("Error occured while reading sum from child!\n");
            return -1;
        }
        close(fd[0]);
        printf("Final Sum of the arry is  %d:", prev_sum + sum);
    }
    return 0;
}