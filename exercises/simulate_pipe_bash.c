#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: run ping and write to file
        int file = open("pingOutput.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (file < 0) {
            perror("open failed");
            exit(1);
        }
        dup2(file, STDOUT_FILENO);
        close(file);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
        perror("execlp failed");  // only runs if execlp fails
        exit(1);
    } else {
        // Parent process: wait, then grep from file
        wait(NULL);
        int file = open("pingOutput.txt", O_RDONLY);
        if (file < 0) {
            perror("open failed");
            return 1;
        }
        dup2(file, STDIN_FILENO);
        close(file);
        execlp("grep", "grep", "rtt", NULL);
        perror("execlp failed");  // only runs if execlp fails
        return 1;
    }

    return 0;
}
