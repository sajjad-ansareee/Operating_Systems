#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread_function(void *argument) {
	while(1) {
		printf("t");
	}
	pthread_exit(NULL);
}

int main(void) {
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread_function, NULL);
	sleep(1/10000000);
	pthread_cancel(thread_1);
	pthread_join(thread_1, NULL);
	return 0;
}