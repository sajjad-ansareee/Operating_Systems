#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
    // execlp("ls", "ls", NULL);
    printf("%d\n", argc);


    // execlp(arg[1], "first", NULL);
    /* Note: The best way for command line execution of file is execlp(arg[1], arg[1], NULL) */


    /* having a number of command line arguments */
    execvp(argv[1], &argv[1]);
    return 0;
}