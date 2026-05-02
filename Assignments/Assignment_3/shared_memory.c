#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>

/* have to be very careful for unlinking and destroying */

/*
Shared Memory
1. get a key(identifier)
2. get shared memory block
3. attach the process which has to use shared memory
4. work on shared memory in each process
5. detach the process from shared memory after completion
6. destroy the shared memory block
*/

#define FILE_NAME "sensor_output"
#define SHM_SIZE 20
#define BUFFER_SIZE 10
#define A_SEM "/a_process"
#define B_SEM "/b_process"
#define C_SEM "/c_process"

int main(int argc, char* argv[]) {
    /* key is a unique identifier */
    key_t key = ftok(FILE_NAME, 0);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char* shared_buffer = (char*)shmat(shmid, NULL, 0);

    sem_t* process_a = sem_open(A_SEM, O_CREAT, 0666, 1); /* process A goes first */
    sem_t* process_b = sem_open(B_SEM, O_CREAT, 0666, 0); /* process B waits */
    sem_t* shm_full =  sem_open(C_SEM, O_CREAT, 0666, 0); /* process C waits for completion */

    int process_c[2];
    pipe(process_c);

    if (!fork()) {
        /* process A section */
        close(process_c[0]);
        close(process_c[1]);
        
        int file = open("sensor_1.txt", O_RDONLY);
        char buffer[BUFFER_SIZE];
        read(file, buffer, BUFFER_SIZE);

        for (int i = 0; i < 10; ++i) {
            sem_wait(process_a); 
            shared_buffer[i * 2] = buffer[i];
            sem_post(process_b); 
        }
        close(file);
        shmdt(shared_buffer);
        exit(0);
    }

    if (!fork()) {
        /* process B in the section */
        close(process_c[0]);
        close(process_c[1]);

        int file = open("sensor_2.txt", O_RDONLY);
        char buffer[BUFFER_SIZE];
        read(file, buffer, BUFFER_SIZE);

        for (int i = 0; i < 10; ++i) {
            sem_wait(process_b); 
            shared_buffer[(i * 2) + 1] = buffer[i];
            sem_post(process_a);
        }
        close(file);
        shmdt(shared_buffer);
        
        sem_post(shm_full); 
        exit(0);
    }

    if (!fork()) {
        /* process C section */
        close(process_c[0]);
        
        sem_wait(shm_full); 
        
        /* read from shared memory and write to the pipe */
        write(process_c[1], shared_buffer, SHM_SIZE);
        close(process_c[1]);
        
        shmdt(shared_buffer);
        exit(0);
    }

    /* parent process section */
    close(process_c[1]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    char buffer[SHM_SIZE + 1];
    memset(buffer, '\0', sizeof(buffer));
    read(process_c[0], buffer, SHM_SIZE);
    
    printf("Parent reading from pipe:\n%s\n", buffer);

    close(process_c[0]);
    sem_close(process_a);
    sem_close(process_b);
    sem_close(shm_full);
    sem_unlink(A_SEM);
    sem_unlink(B_SEM);
    sem_unlink(C_SEM);
    
    shmdt(shared_buffer);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}