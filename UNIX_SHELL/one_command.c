#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc==1) {
        perror("No command line argument given\n");
        return 0;
    }
    execvp(argv[1], &argv[1]);
    return 0;
}