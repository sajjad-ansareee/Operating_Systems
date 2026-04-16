#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *arg[]) {
    mkfifo("fifo", 0666);
    /* child process here */
    if (!fork()) {
        int write_file=open("fifo", O_WRONLY);
        const int buffer_size=1024;
        char buffer[]="I am child\n";
        printf("Waiting for reader\n");

        /* Note: Always use strlen(buffer)+1, to include the '\0' otherwise undefined behavior can be there */

        int write_count=write(write_file, buffer, strlen(buffer)+1);
        close(write_file);
        exit(0);
    }
    /* parent process here */
    else {
        // wait(NULL); /* there would be deadlock with this wait */
        int read_file=open("fifo", O_RDONLY);
        wait(NULL);
        const int buffer_size=1024;
        char buffer[buffer_size];
        int read_count=read(read_file, buffer, buffer_size);
        printf("%s\n", buffer);
        close(read_file);
    }
    return 0;
}