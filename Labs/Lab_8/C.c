#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int shared_memory;

void *writer_function(void *argument) {
	// pthread_mutex_lock(&shared_memory);
	printf("Shared data: ");
	scanf("%d", &shared_memory);
	// pthread_mutex_unlock(&shared_memory);
	pthread_exit(NULL);
}

void *reader_function(void *argument) {
	printf("%d", shared_memory);
	pthread_exit(NULL);
}

int main(void) {
	int n;
	printf("Number of readers: "); scanf("%d", &n);
	pthread_t writer;
	pthread_t *reader=malloc(n*sizeof(pthread_t));
	while(1){
		pthread_create(&writer, NULL, writer_function, NULL);
		for (int i=0;i<n;++i) {
			pthread_create(&reader[i], NULL, reader_function, NULL);
			pthread_join(reader[i], NULL);
		}
		pthread_join(writer, NULL);
	}
	free(reader);
	reader=NULL;
	return 0;
}