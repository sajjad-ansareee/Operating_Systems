#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PARENT_SEM "/parent_semaphore"
#define CHILD_SEM "/child_semaphore"
#define FILE_NAME "file.txt"
#define BUFFER_SIZE 1024

/* 
Named Semaphore:
1. open
2. wait/post
3. close    (it would close for the specific process only)
4. unlink   (it finally removes the semaphore)
*/

int main(int argc, char* argv[]) {
    /* semaphore acting as binary */
    sem_t* parent_semaphore=sem_open(PARENT_SEM, O_CREAT, 0666, 0);
    sem_t* child_semaphore=sem_open(CHILD_SEM, O_CREAT, 0666, 0);
    if (!fork()) {
        /* first child in condition */
        if (!fork()) {
            /* grand child in the condition */
            int file=open(FILE_NAME, O_CREAT|O_WRONLY|O_TRUNC, 0644);
            char buffer[BUFFER_SIZE]="INIT\n";
            int write_count=write(file, buffer, strlen(buffer));
            sem_post(child_semaphore);
            sem_close(parent_semaphore);
            sem_close(child_semaphore);
            close(file);
            exit(0);
        }
        sem_wait(child_semaphore);
        int file=open(FILE_NAME, O_WRONLY|O_APPEND);
        char buffer[BUFFER_SIZE]="PROCESSED\n";
        int write_count=write(file, buffer, strlen(buffer));
        sem_post(parent_semaphore);
        sem_close(parent_semaphore);
        sem_close(child_semaphore);
        close(file);
        exit(0);
    }
    /* parent here */
    sem_wait(parent_semaphore);
    int file=open(FILE_NAME, O_RDONLY);
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);
    int read_count=read(file, buffer, BUFFER_SIZE);
    printf("%s", buffer);
    sem_close(parent_semaphore);
    sem_close(child_semaphore);
    sem_unlink(PARENT_SEM);
    sem_unlink(CHILD_SEM);
    return 0;
}