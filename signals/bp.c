#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int x;
    printf("Enter a number:\n");
    scanf("%d", &x); //the process receives SIGTSTP on CTRL+Z

    printf("Result: %d\n", x*5);
    return 0;

}