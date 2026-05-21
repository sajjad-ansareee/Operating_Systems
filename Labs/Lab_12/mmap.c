/* truncate method */

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
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>

#define FILE_NAME "data.txt"
#define FILE_SIZE 100

int main(int argc, char *argv[]) {
    const char* message=" - Updated\n";
    int file=open(FILE_NAME, O_RDWR);
    int file_size=lseek(file, 0, SEEK_END);
    /* it allocates the given size in bytes to the given file descriptor */
    ftruncate(file, file_size+strlen(message));
    char* data=(char*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
    printf("Before: %s", data);
    strcat(data, message);
    // strncpy(data, message, strlen(message));
    printf("After: %s", data);
    munmap(data, FILE_SIZE);
    close(file);
    return 0;
}