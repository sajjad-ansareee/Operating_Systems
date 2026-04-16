#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4

typedef struct {
	int *array;
	int start;
	int end;
} ThreadData;

void *get_sum(void *argument) {
	ThreadData *data = (ThreadData*)argument;
	long *partial_sum = malloc(sizeof(long));
	*partial_sum = 0;
	for (int i = data->start; i < data->end; ++i) {
		*partial_sum += data->array[i];
	}
	pthread_exit((void*)partial_sum);
}
int main(void) {
	int array[ARRAY_SIZE];
	pthread_t threads[NUM_THREADS];
	ThreadData thread_data[NUM_THREADS];
	// a. Initialize array with random values
	srand(time(NULL));
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array[i] = rand() % 100; // Random numbers 0-99
	}
	int segment_size = ARRAY_SIZE / NUM_THREADS;
	for (int i = 0; i < NUM_THREADS; i++) {
		thread_data[i].array = array;
		thread_data[i].start = i * segment_size;
		thread_data[i].end = (i + 1) * segment_size;
		pthread_create(&threads[i], NULL, get_sum, &thread_data[i]);
	}
	long total_sum = 0;
	for (int i = 0; i < NUM_THREADS; i++) {
		void *return_val;
		pthread_join(threads[i], &return_val);
		long *partial = (long*)return_val;
		total_sum += *partial;
		printf("Thread %d finished. Partial sum: %ld\n", i + 1, *partial);
		free(partial); // Clean up allocated memory from thread
	}
	printf("\nTotal Sum of 1000 elements: %ld\n", total_sum);
	return 0;
}