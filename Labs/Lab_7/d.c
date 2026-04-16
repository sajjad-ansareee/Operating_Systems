#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

void* increment_counter(void* arg) {
	for (int i = 0; i < 10000; i++) {
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main() {
	pthread_t threads[5];
	pthread_mutex_init(&lock, NULL);
	for (int i = 0; i < 5; i++) {
		if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
			perror("Failed to create thread");
		}
	}

	for (int i = 0; i < 5; i++) {
		pthread_join(threads[i], NULL);
	}
	printf("Final Counter Value: %d\n", counter);
	printf("Expected Value: 50000\n");
	pthread_mutex_destroy(&lock);
	return 0;
}