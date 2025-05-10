// A process consists of -

// 1. Program Counter (PC): Keeps track of which instruction to execute next.

// 2. Memory:

    // Code segment (the instructions),

    // Data segment (global/static variables),

    // Heap (dynamically allocated memory),

    // Stack (function calls and local variables).

// 3. Process ID (PID): A unique number assigned by the OS.

// 4. Execution State: Can be ready, running, waiting, terminated, etc.

// 5. Resources: Each process has its own set of file handles, memory space, etc.

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[]){
    int id = fork();
    // a child process is created from the parent processes that executes alongside the parent process after fork is called.
    // Threrfore 2 different ID's are returned from fork and the rest of the code executes in both the processes.
    // Process_id of 0 implies we are in the child process.
    if(id == 0){
        printf("Hello World from child\n");
    }else{
        printf("Hello from parent\n");
    }
    return 0;
}

