#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define SIZE 1024

void write_file() {
  int file=open("file.txt", O_WRONLY);
  char buffer[]="Write Function!\n";
  int write_count=write(file, buffer, strlen(buffer));
  close(file);
}