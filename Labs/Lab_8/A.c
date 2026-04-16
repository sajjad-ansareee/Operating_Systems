#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Fixed-size buffer

int buffer[BUFFER_SIZE];
int in = 0;  // Index for Producer
int out = 0; // Index for Consumer

sem_t mutex;
sem_t empty;
sem_t full;

void* Producer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        item = rand() % 100; // Produce an item

        sem_wait(&empty);    // Wait for an empty slot (decrement empty)
        sem_wait(&mutex);    // Enter critical section

        // Add to buffer
        buffer[in] = item;
        printf("Producer inserted: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);    // Leave critical section
        sem_post(&full);     // Signal that a slot is full (increment full)

        sleep(1);
    }
    return NULL;
}

void* Consumer(void* arg) {
    int item;
    for(int i = 0; i < 10; i++) {
        sem_wait(&full);     // Wait for a full slot (decrement full)
        sem_wait(&mutex);    // Enter critical section

        // Remove from buffer
        item = buffer[out];
        printf("Consumer removed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);    // Leave critical section
        sem_post(&empty);    // Signal that a slot is empty (increment empty)

        sleep(2); // Consumer is slower than producer
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    // Initialize Semaphores
    sem_init(&mutex, 0, 1);           // Binary mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Starts at BUFFER_SIZE
    sem_init(&full, 0, 0);            // Starts at 0

    pthread_create(&prod_tid, NULL, Producer, NULL);
    pthread_create(&cons_tid, NULL, Consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}