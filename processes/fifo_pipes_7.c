#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

// Any process can be write into a named pipe!
int main(int argc, char * argv[]){
    // Similar to file where any process can read or write into

    // Creates a new file to write into
    if(mkfifo("myfifo1", 0777) == -1){// signature -> (name, permission bits) -> error code
        if(errno != EEXIST){
            printf("Could not create FIFO file");
            return -1;
        }
    }

    // CHARACTERISTIC OF NAMED PIPES -> THE PROCESS OPENING THE FIFO FILE BLOCKS UNTIL THERE IS ANOTHER PROCESS THAT READS FROM THE FIFO FILE
    printf("opening the file\n");
    
    int fd = open("myfifo1", O_WRONLY);
    printf("opened the file\n");
    int x = 97;
    if(write(fd, &x, sizeof(int))== -1){
        printf("Write Failed!");
        return -1;
    }
    printf("written to the file\n");

    close(fd);
    printf("closed the file\n");


    return 0;
} 