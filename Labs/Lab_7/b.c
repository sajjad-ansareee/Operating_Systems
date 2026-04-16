#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *first(void *argument) {
	int n=*((int*)argument);
	unsigned long *result=malloc(sizeof(unsigned long));
	*result=1;
	for (int i=n; i>1; --i) {
		(*result)*=i;
	}
	pthread_exit((void*)result);
}

int main(void) {
	pthread_t first_thread, second_thread;
	int n_1=5, n_2=6;
	pthread_create(&first_thread, NULL, first, &n_1);
	void *thread_result;
	pthread_join(first_thread, &thread_result);
	unsigned long *result=(unsigned long*)thread_result;
	printf("Factorial=%lu\n", *result);

	pthread_create(&second_thread, NULL, first, &n_2);
	pthread_join(second_thread, &thread_result);
	unsigned long *result_2=(unsigned long*)thread_result;
	printf("Factorial=%lu\n", *result_2);
	return 0;
}