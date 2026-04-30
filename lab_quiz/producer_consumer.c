#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE
int buffer[BUFFER_SIZE];

sem_t mutex;
sem_t full;
sem_t empty;

int main(int argc, char* argv[]) {
    /* initially no producer is using the critical section */
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 1);
    return 0;
}