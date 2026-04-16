#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>

#define SHM_SIZE 1024
#define THRESHOLD 35.0

// Helper structure for semaphore operations
struct sembuf p = {0, -1, SEM_UNDO}; // Wait (P) operation
struct sembuf v = {0, 1, SEM_UNDO};  // Signal (V) operation

int main() {
    key_t key = ftok("shmfile", 65);
    
    // 1. Create Shared Memory
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    float *shm_ptr = (float*) shmat(shmid, NULL, 0);

    // 2. Create Semaphore (1 semaphore in the set)
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 1); // Initialize semaphore to 1 (Unlocked)

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    
    if (pid == 0) { // SENSOR PROCESS (Producer)
        srand(time(NULL));
        for(int i = 0; i < 5; i++) {
            float temp = 20.0 + (float)(rand() % 200) / 10.0; // Random temp 20-40

            semop(semid, &p, 1); // Lock
            *shm_ptr = temp;
            printf("[Sensor] Writing Temperature: %.2f°C\n", temp);
            semop(semid, &v, 1); // Unlock

            sleep(1); 
        }
        shmdt(shm_ptr);
        exit(0);
    } 
    else { // DISPLAY PROCESS (Consumer)
        for(int i = 0; i < 5; i++) {
            sleep(1); // Read every second

            semop(semid, &p, 1); // Lock
            float current_temp = *shm_ptr;
            printf("[Display] Current Temp: %.2f°C", current_temp);
            
            if (current_temp > THRESHOLD) {
                printf(" --- ALERT: THRESHOLD EXCEEDED! ---");
            }
            printf("\n");
            semop(semid, &v, 1); // Unlock
        }

        // Cleanup
        wait(NULL);
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL); // Destroy shared memory
        semctl(semid, 0, IPC_RMID);    // Destroy semaphore
        printf("Resources cleaned up. Parent exiting.\n");
    }

    return 0;
}