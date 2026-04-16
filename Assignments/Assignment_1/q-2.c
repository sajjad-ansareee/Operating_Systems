// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <sys/pidfd.h>
//
// int main(int argc, char *arg[]) {
//   // Parent inside
//   if (fork()) {
//     // Second child
//     if (!fork()) {
//       execlp("wc", "wc", arg[1], NULL);
//     }
//     else {
//       wait(NULL);
//       wait(NULL);
//     }
//   }
//   // First Child
//   else {
//     execlp("cat", "cat", arg[1], NULL);
//   }
//   return 0;
// }