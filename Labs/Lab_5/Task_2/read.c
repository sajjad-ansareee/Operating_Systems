#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define SIZE 1024

void read_file() {
  int file=open("file.txt", O_RDONLY);
  char buffer[SIZE];
  int read_count=read(file, buffer, SIZE);
  buffer[read_count]='\0';
  printf("Read from file:\n%s\n", buffer);
  close(file);
}