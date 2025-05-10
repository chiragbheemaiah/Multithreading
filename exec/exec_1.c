#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>



int main(int argc, char* argv[]){
    // the execl loads a new process on top of existing process, rewriting memory of the current process.
    // Gnerally, the exec famly is used with forking processes.
    execl("/usr/bin/ping", "/usr/bin/ping", "google.com", NULL); //signature -> (path, path, args....., NULL), L - LIST
    // IMPORTANT: The exec command is used to execute an executable, it is not a bash terminal, therefore - ping google.com | grp rtt will not work
    printf("Completed!"); //wont be printed


    // execlp(ping, "usr/bin/ping", "google.com", NULL); -> loads the path variable in.
    // execvp() -> pass a char array; execvp("ping", arr); char* arr[] = {"ping", "google.com", NULL};
    // execvpe -> environment setting as a char array
    return 0;
}