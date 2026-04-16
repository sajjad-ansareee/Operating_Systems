// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <sys/pidfd.h>
//
// void initialize(char matrix[][4]) {
//   printf("Enter the matrix: \n");
//   //Character for ignoring new line character while taking input
//   char ignore;
//   for (int i=0;i<4;++i) {
//     printf("Enter %d row: ", i);
//     for (int j=0;j<4;++j) {
//       scanf("%c", &matrix[i][j]);
//     }
//     scanf("%c", &ignore);
//   }
// }
//
// void display(char matrix[][4]) {
//   printf("The matrix:\n");
//   for (int i=0;i<4;++i) {
//     for (int j=0;j<4;++j) {
//       printf("%c ", matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
//
// void task(char matrix[][4]) {
//   pid_t c_pid=fork();
//   // Parent in the condition
//   if (c_pid) {
//     int status;
//     c_pid=fork();
//     if (c_pid) {
//       return_pid=wait(&status); /* Waiting for the second child */
//       int total_border=WEXITSTATUS(status);
//       printf("Border Contribution: %d\n", (total_border*100)/total_black);
//       // Finally the parent has shown both the results
//       printf("Parent calculated both densities\n");
//       pid_t return_pid=wait(&status); /* Waiting for the first child */
//       int total_black=WEXITSTATUS(status);
//       printf("Black pixel density: %d\n", (total_black*100)/16);
//     }
//     else {
//       // Second child calculating the border black cells
//       int count=0;
//       for (int i=0;i<4;++i) {
//         for (int j=0;j<4;++j) {
//           if ((i==0 || j==0 || i==4 || j==4)&&(matrix[i][j]=='B')) {
//             count++;
//           }
//         }
//       }
//       exit(count);
//     }
//   }
//   else {
//   // First child calculating total black cells
//     int count=0;
//     for (int i=0;i<4;++i) {
//       for (int j=0;j<4;++j) {
//         if (matrix[i][j]=='B') {
//           count++;
//         }
//       }
//     }
//     exit(count);
//   }
// }
//
// int main() {
//   char matrix[4][4];
//   initialize(matrix);
//   display(matrix);
//   task(matrix);
//   return 0;
// }