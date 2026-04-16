#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

/* the arguments are always copied as it is even the ./main */

int main(int argc, char *arg[]) {
    printf("%d\n", argc);
    printf("%s\n", arg[0]);
    int read_file=open(arg[1], O_RDONLY);
    const int buffer_size=1024;
    char buffer[buffer_size];
    int read_count=read(read_file, buffer, buffer_size);
    printf("%s\n", buffer);
    close(read_file);
    return 0;
}