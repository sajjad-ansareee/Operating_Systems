#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    int input_file=open("input.txt", O_RDONLY|O_CREAT);
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);
    int read_count=read(input_file, buffer, BUFFER_SIZE);
    
    return 0;
}