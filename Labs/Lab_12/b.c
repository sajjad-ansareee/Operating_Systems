#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>

#define FILE_SIZE 100

typedef struct {
    char* data;
    int start;
    int end;
} ThreadArgument;

void* thread_function(void* argument) {
    ThreadArgument t=*(ThreadArgument*)argument;
    for (int i=t.start; i<=t.end; ++i) {
        if (t.data[i]>='0' && t.data[i]<='9') {
            t.data[i]=' ';
        }
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    int file=open(argv[1], O_RDWR);
    ftruncate(file, FILE_SIZE);
    ThreadArgument* t=malloc(sizeof(ThreadArgument));
    t->data=mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
    t->start=0;
    t->end=50;
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_function, (void*)t);
    pthread_join(t1, NULL);
    t->start=51;
    t->end=100;
    pthread_create(&t2, NULL, thread_function, (void*)t);
    // pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("%s", t->data);
    munmap(t->data, FILE_SIZE);
    close(file);
    free(t);
    return 0;
}