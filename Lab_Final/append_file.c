/* O_TRUNC is used to wipe the contents of the file */

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
    int file=open(FILE_NAME, O_APPEND|O_WRONLY);
    const char* message="Testing the appending\n";
    int write_count=write(file, message, strlen(message));
    close(file);
    return 0;
}