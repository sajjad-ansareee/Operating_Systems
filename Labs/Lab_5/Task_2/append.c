#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define SIZE 1024

void append_file() {
  int file=open("file.txt", O_CREAT | O_WRONLY | O_APPEND);
  char buffer[]="Append Function!\n";
  int write_count=write(file, buffer, strlen(buffer));
  close(file);
}