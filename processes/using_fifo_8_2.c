#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include<fcntl.h>
#include<sys/types.h>
#include<errno.h>


int main(int argc, char* argv[]){
    int arr[5];
    int fd = open("sum", O_RDONLY);
    if(fd == -1){
        return -1;
    }

    for(int i =0; i < 5; i++){
        if(read(fd, &arr[i], sizeof(int)) == -1){
            printf("Writing failed!\n");
            return -1;
        }
    }
    
    printf("Finished receiving stuff!\n");
    int sum = 0;
    for(int i =0; i < 5; i++){
        sum += arr[i];
        printf("%d\n", arr[i]);
    }

    close(fd);
    fd = open("sum", O_WRONLY);
    if(fd == -1){
        printf("Opening file sum failed!");
        return -1;
    }
    if(write(fd, &sum, sizeof(int)) == -1){
        printf("Writing file sum failed");
        return -1;
    }
    close(fd);
    return 0;
}