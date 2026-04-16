#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

pthread_mutex_t count;

int counter=0;

void *thread_function(void *argument) {
    pthread_mutex_lock(&count);     /* have to mention the critical variable here otherwise error */
    for (int i=0; i<100000; ++i) {
        counter++;
    }
    pthread_mutex_unlock(&count);
    pthread_exit(NULL);
}

int main(int argc, char *arg[]) {
    /* pthread_mutex_init(pthread_mutex_t, pthread_mutex_attribute *value) */
    // pthread_mutex_init(&count, NULL);
    pthread_t thread_1, thread_2;
    pthread_create(&thread_1, NULL, thread_function, NULL);
    pthread_create(&thread_2, NULL, thread_function, NULL);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    printf("%d\n", counter);
    return 0;
}