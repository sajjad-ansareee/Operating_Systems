#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

#define PIPE "/my_fifo"
#define RANDOM_COUNT 50
#define FULL "/buffer_full"
#define EMPTY "/buffer_empty"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    sem_t* sem_full=sem_open(FULL, O_CREAT, 0666, RANDOM_COUNT);
    sem_t* sem_empty=sem_open(EMPTY, O_CREAT, 0666, 0);
    mkfifo(PIPE, 0666);
    int file=open(PIPE, O_WRONLY);
    for (int i=0; i<RANDOM_COUNT; ++i) {
        int random_number=rand()%101;           /* the number range is constrained */
        sem_wait(sem_full);
        write(file, &random_number, sizeof(int));
        sem_post(sem_empty);
    }
    close(file);
    sem_close(sem_full);
    sem_close(sem_empty);
    /* not unlinked here as another file also using same semaphore */
    return 0;
}