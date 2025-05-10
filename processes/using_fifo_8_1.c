#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include<fcntl.h>
#include<sys/types.h>
#include<errno.h>


int main(int argc, char* argv[]){
    int arr[5] = {1,2,3,4,5};
    int fd = open("sum", O_WRONLY);
    if(fd == -1){
        return -1;
    }

    for(int i =0; i < 5; i++){
        if(write(fd, &arr[i], sizeof(int)) == -1){
            printf("Writing failed!\n");
            return -1;
        }
    }
    printf("Finished writing stuff!\n");
    close(fd);

    int sum;
    fd = open("sum", O_RDONLY);
    if(fd == -1){
        printf("Opening file sum failed!");
        return -1;
    }
    if(read(fd, &sum, sizeof(int)) == -1){
        printf("Reading file sum failed");
        return -1;
    }
    close(fd);
    printf("Received sum : %d", sum);
    return 0;
}