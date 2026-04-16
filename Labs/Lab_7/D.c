#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter=0;

pthread_mutex_t count;

void *thread_function(void *argument) {
	char c=*((char*)argument);
	pthread_mutex_lock(&count);
	for (int i=0;i<10000;++i) {
		counter+=1;
		printf("%c", c);
	}
	pthread_mutex_unlock(&count);
	pthread_exit(NULL);
}

int main() {
	pthread_mutex_init(&count, NULL);
	pthread_t thread_1, thread_2;
	pthread_create(&thread_1, NULL, thread_function, "a");
	pthread_create(&thread_2, NULL, thread_function, "b");
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_mutex_destroy(&count);
	printf("Counter=%d\n", counter);
	return 0;
}