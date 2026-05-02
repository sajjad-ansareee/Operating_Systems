#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

#define FULL "/buffer_full"
#define EMPTY "/buffer_empty"
#define PIPE "/my_fifo"

int main(int argc, char* argv[]) {
    sem_t* sem_full=sem_open(FULL, 0);
    sem_t* sem_empty=sem_open(EMPTY, 0);
    int sum=0;
    int file=open(PIPE, O_RDONLY);
    for (int i=0; i<50; ++i) {
        sem_wait(sem_empty);
        int number;
        read(file, &number, sizeof(int));
        sum+=number;
        sem_post(sem_full);
    }
    printf("Sum: %d\n", sum);
    close(file);
    sem_close(sem_full);
    sem_close(sem_empty);
    return 0;
}