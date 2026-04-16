#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024

void copy(char read_name[], char write_name[]) {
  int read_file=open(read_name, O_RDONLY);
  char buffer[SIZE];
  int read_count=read(read_file, buffer, SIZE);
  buffer[read_count]='\0';
  int write_file=open(write_name, O_WRONLY);
  write(write_file, buffer, read_count);
}

int main(int argc, char *arg[]) {
  copy(arg[1], arg[2]);
  return 0;
}