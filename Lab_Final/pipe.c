#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    if (!fork()) {
        /* child in the condition */
        close(fd[0]);   /* child is only writing to parent */
        const char* message="My name is Sajjad";
        write(fd[1], message, strlen(message));
        close(fd[1]);
        exit(0);
    }
    /* parent here */
    wait(NULL);
    close(fd[1]);
    char buffer[BUFFER_SIZE];
    // memset(buffer, '\0', BUFFER_SIZE);
    read(fd[0], buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
    printf("%c\n", buffer[100]);
    close(fd[0]);
    return 0;
}