#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define BUFFER_SIZE 0
int buffer[BUFFER_SIZE];
int producer_index=0;
int consumer_index=0;

sem_t mutex;
sem_t full;
sem_t empty;

void *producer(void *argument) {
    sem_wait(&full);
    sem_wait(&mutex);
    buffer[producer_index]=rand()%100;
    producer_index=((producer_index+1)%BUFFER_SIZE);
    sem_post(&mutex);
    /* signal something is written in buffer so can read it */
    sem_post(&empty);
    return NULL;
}

void *consumer(void *argument) {
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[consumer_index]=rand()%100;
    consumer_index=((consumer_index+1)%BUFFER_SIZE);
    sem_post(&mutex);
    /* signal something is written in buffer so can read it */
    sem_post(&full);
    return NULL;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    /* initially no producer is using the critical section */
    sem_init(&mutex, 0, 1);
    /* the buffer is not full so can add items */
    sem_init(&full, 0, BUFFER_SIZE);
    /* considering initially the buffer is empty */
    sem_init(&empty, 0, 0);
    return 0;
}