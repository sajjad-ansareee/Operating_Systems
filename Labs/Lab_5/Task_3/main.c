#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *arg[]) {
  if (fork()) {
    wait(NULL);
  }
  else {
    execlp("./copy", "./copy", arg[1], arg[2], NULL);
    exit(-1);
  }
  return 0;
}