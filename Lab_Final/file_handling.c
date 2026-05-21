/* the read and write commands are blocked until another process is opening the file for vice versa */

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

#define FILE_NAME   "file.txt"
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    int file=open(FILE_NAME, O_RDONLY);
    char buffer[BUFFER_SIZE];
    // memset(buffer, '\0', BUFFER_SIZE);
    int read_count=read(file, buffer, BUFFER_SIZE);
    printf("%s\n", buffer);
    // char storing_buffer[BUFFER_SIZE];
    // sprintf(storing_buffer, buffer);
    close(file);
    return 0;
}