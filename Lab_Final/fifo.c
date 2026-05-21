/* we are having the mode here */
/* for read write there is option for flags */
/* whenever see a mode or flag argument use the mkfifo function first */

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

#define FIFO "testing_fifo"
#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    mkfifo(FIFO, 0666);
    int file=open(FIFO, O_WRONLY);
    const char* message="My name is Sajjad!";
    int write_count=write(file, message, strlen(message));
    printf("Successfully written!\n");
    close(file);
    return 0;
}