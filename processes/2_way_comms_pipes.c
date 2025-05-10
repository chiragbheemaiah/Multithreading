#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    int x = 5;
    int fd1[2], fd2[2];
    if(pipe(fd1) == -1){
        printf("Error creating a pipe!");
        return -1;
    }
    if(pipe(fd2) == -1){
        printf("Error creating a pipe!");
        return -1;
    }
    
    int id = fork();
    if (id == -1){
        printf("Forking failed!");
        return -1;
    }
    if(id == 0){
        // child process
        int x;
        close(fd1[1]);
        if(read(fd1[0], &x, sizeof(int)) == -1){
            printf("reading failed in child!");
            return -1;
        }
        int prod;
        prod = x * 4;
        close(fd2[0]);
        if(write(fd2[1], &prod, sizeof(int)) == -1){
            printf("Writing data in child failed!");
            return -1;
        }
        close(fd2[0]);
    }
    else{
        int x = 5;
        int res;
        close(fd1[0]);
        if(write(fd1[1], &x, sizeof(int)) == -1){
            printf("Writing data in parent failed!");
            return -1;
        }
        close(fd1[1]);

        close(fd2[1]);
        if(read(fd2[0], &res, sizeof(int))  == -1){
            printf("Reading failed in parent!");
            return -1;
        }
        close(fd2[0]);

        printf("The final result is %d", res);
    }
    return 0;
}