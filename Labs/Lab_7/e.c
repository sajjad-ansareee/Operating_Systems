#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *foo(void *argument) {
	while (1) {
		printf("Hi\n");
	}
	return NULL;
}

int main(void) {
	pthread_t thread;
	pthread_create(&thread, NULL, foo, NULL);
	sleep((1/4));
	pthread_cancel(thread);
	return 0;
}