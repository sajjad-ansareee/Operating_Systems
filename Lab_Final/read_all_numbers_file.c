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

#define FILE_NAME "file.txt"

int main(int argc, char *argv[]) {
    int file=open(FILE_NAME, O_RDONLY);
    dup2(file, STDIN_FILENO);
    int number;
    int sum=0;
    while(scanf("%d", &number)!=-1) {
        sum+=number;
    }
    printf("The Sum: %d\n", sum);
    return 0;
}