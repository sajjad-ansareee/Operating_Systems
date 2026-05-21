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
#include <sys/mman.h>
#include <pthread.h>
#include <semaphore.h>

int counter=0;

int main(int argc, char *argv[]) {
    if(!fork()) {
        for (int i=0; i<100; ++i) {
            counter+=1;
        }
        exit(1);
    }
    int status;
    wait(&status);
    /* return status of the child process */
    printf("%d\n", WEXITSTATUS(status));
    for (int i=0; i<100; ++i) {
        counter+=1;
    }
    /* gives the output 100 */
    printf("%d\n", counter);
    /* getting the process id of current process */
    printf("%d\n", getpid());
    return 0;
}