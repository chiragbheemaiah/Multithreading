#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        return -1;
    }
    int id = fork();
    if(id == -1){
        return -2;
    }
    if(id == 0){
        char string[100];
        printf("String enter please \n");
        fgets(string, sizeof(string), stdin);
        int n;
        for(int i=0;i<100;i++){
            n += 1;
            if (string[i] == '\0'){
                break;
            }
        }
        close(fd[0]);
        if(write(fd[1], &n, sizeof(int)) == -1){
            return -3;
        }
        if(write(fd[1], string, sizeof(char) * n) == -1){
            return -4;
        }
        close(fd[1]);
    }else{
        int n;
        char res[100];
        close(fd[1]);
        if(read(fd[0], &n, sizeof(int)) == -1){
            return -5;
        }
        if(read(fd[0],res, sizeof(char) * n) == -1){
            return -6;
        }
        close(fd[0]);
        wait(NULL);
        printf("Received string : %s\n", res);
    }
    return 0;
}