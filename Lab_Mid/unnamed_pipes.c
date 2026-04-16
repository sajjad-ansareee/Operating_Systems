#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

/* unnamed pipes are actully use to communicate between two related processes */
void parent_child_communication() {
    int fd[2];
    pipe(fd);   /* fd[0] for reading, fd[1] for writing */
    // child inside the condition
    if (!fork()) {
        close(fd[0]); /* first step is to close the not using descriptors */
        char write_message[]="Hello, Papa!\n";
        write(fd[1], write_message, strlen(write_message));
        close(fd[1]);
        // exit(int status)
        exit(0);        /* child should exit through the exit statement otherwise undefined behavior */
    }
    // parent inside the condition
    else {
        close(fd[1]);
        // wait(int *child_return_status)
        int child_status;
        wait(&child_status);
        printf("%d", child_status);
        const int buffer_size=1024;
        char buffer[buffer_size];
        read(fd[0], buffer, buffer_size);
        printf("%s\n", buffer);
        close(fd[0]);
        // exit(0);     /* parent should be exit through the return statement otherwise undefined behavior */
        // parent is still here and will go to part of main function after the function call
    }
}

int main(int argc, char *arg[]) {
    parent_child_communication();
    return 0;
}