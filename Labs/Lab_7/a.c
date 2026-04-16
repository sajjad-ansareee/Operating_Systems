#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *first_routine(void *argument) {
	printf("Hello from thread id:%lu\n", pthread_self());
	return NULL;
}

void *second_routine(void *argument) {
	printf("Hello from thread id:%lu\n", pthread_self());
	return NULL;
}

void *third_routine(void *argument) {
	printf("Hello from thread id:%lu\n", pthread_self());
	return NULL;
}

int main(void) {
	pthread_t first_thread, second_thread, third_thread;
	pthread_create(&first_thread, NULL, first_routine, NULL);
	pthread_create(&second_thread, NULL, second_routine, NULL);
	pthread_create(&third_thread, NULL, third_routine, NULL);
	pthread_join(first_thread, NULL);
	pthread_join(second_thread, NULL);
	pthread_join(third_thread, NULL);
	return 0;
}