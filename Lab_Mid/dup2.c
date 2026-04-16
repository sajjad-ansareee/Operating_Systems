#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *arg[]) {
    int write_file=open("write_file.txt", O_WRONLY);
    /* dup2(old_file_descriptor, new_file_descriptor) */
    dup2(write_file, 1);
    printf("Sajjad\n");
    // close(STDOUT_FILENO);    /* never close the standard_output file */
    // close(write_file);       /* it is already closed no purpose of closing here */
    printf("Ansari\n");
    return 0;
}