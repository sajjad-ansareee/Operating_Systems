#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define FILE_NAME "existing_file.txt"
#define SHM_SIZE 20

int main(int argc, char* argv[]) {
    /* it demands an existing and accessible file */
    key_t key=ftok(FILE_NAME, 0);
    int shm_id=shmget(key, SHM_SIZE, 0);
    char* buffer=(char*)shmat(shm_id, NULL, 0);
    shmdt(buffer);
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}