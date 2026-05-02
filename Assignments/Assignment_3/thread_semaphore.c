#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/*
Thread Semaphore
1. create global semaphore
2. initialize in main for once
3. use wait/post in thread function
4. destroy the semaphore in main
*/

#define BOOTH 3
#define BUFFER_SIZE 1024
#define FILE_NAME "corona.txt"
int corona_patient=0;
sem_t potential_c;
pthread_mutex_t critical_section;

void* thread_function(void* argument) {
    sem_wait(&potential_c);
    int file=*(int*)argument;
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);
    if (rand()%2) {
        /* locked the critical section for race condition */
        pthread_mutex_lock(&critical_section);
        corona_patient+=1;
        pthread_mutex_unlock(&critical_section);
        sprintf(buffer, "%lu Infected\n", (unsigned long)pthread_self());
    }
    else {
        sprintf(buffer, "%lu Not Infected\n", (unsigned long)pthread_self());
    }
    int write_count=write(file, buffer, strlen(buffer));
    sem_post(&potential_c);
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    sem_init(&potential_c, 0, BOOTH);
    pthread_mutex_init(&critical_section, NULL);
    int file=open(FILE_NAME, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int n;
    printf("Number of patients: "); scanf("%d", &n);
    pthread_t* patients=malloc(n*sizeof(pthread_t));
    for (int i=0; i<n; ++i) {
        pthread_create(&patients[i], NULL, thread_function, &file);
    }
    for (int i=0; i<n; ++i) {
        pthread_join(patients[i], NULL);
    }
    sem_destroy(&potential_c);
    pthread_mutex_destroy(&critical_section);
    close(file);
    return 0;
}