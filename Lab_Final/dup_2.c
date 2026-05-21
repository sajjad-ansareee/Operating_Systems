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

#define FILE_NAME "file.txt"

int main(int argc, char *argv[]) {
    int my_stdout=open(FILE_NAME, O_WRONLY);
    dup2(my_stdout, STDOUT_FILENO);
    printf("Hello from Sajjad\n");
    close(my_stdout);
    return 0;
}