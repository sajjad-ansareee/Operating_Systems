/* 
    parent send a string to child
    child modifies the stirng
    child send back the string
    parent print the modified string 
*/

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

#define BUFFER_SIZE 1000

int main(int argc, char *argv[]) {
    int parent_to_child[2];
    int child_to_parent[2];
    pipe(parent_to_child);
    pipe(child_to_parent);
    if (!fork()) {
        /* child here */
        close(parent_to_child[1]);
        close(child_to_parent[0]);
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        int read_count=read(parent_to_child[0], buffer, BUFFER_SIZE);
        close(parent_to_child[0]);
        for (int i=0; i<strlen(buffer); ++i) {
            if (buffer[i]=='@') {
                buffer[i]=' ';
            }
        }
        int write_count=write(child_to_parent[1], buffer, strlen(buffer));
        close(child_to_parent[1]);
        exit(0);
    }
    /* parent here */
    close(parent_to_child[0]);
    close(child_to_parent[1]);
    char buffer[BUFFER_SIZE];
    printf("Enter a random string: ");
    // scanf("%s", buffer);
    fgets(buffer, BUFFER_SIZE, stdin);
    printf("Old String: %s\n", buffer);
    int write_count=write(parent_to_child[1], buffer, strlen(buffer));
    close(parent_to_child[1]);
    memset(buffer, '\0', BUFFER_SIZE);
    int read_count=read(child_to_parent[0], buffer, BUFFER_SIZE);
    printf("Modified String: %s\n", buffer);
    close(child_to_parent[0]);
    return 0;
}