#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int id1 = fork();
    int id2 = fork();
    if(id1 == 0){
        if(id2 == 0){
            printf("Process D");
        }
        else{
            printf("Process B");
        }
    }
    else{
        if(id2 == 0){
            printf("Process C");
        }
    else{
        printf("Process A");
    }
    }

}