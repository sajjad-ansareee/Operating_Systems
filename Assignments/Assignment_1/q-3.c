// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <sys/pidfd.h>
// #include <time.h>
//
// int max(int a, int b) {
//   return a>=b?a:b;
// }
//
// int merge_maximum(int L, int R, int *array) {
//   int maximum=0;
//   // Search for the maximum in array and return it
//   if (R-L<=10) {
//     for (int i=L;i<=R;++i) {
//       maximum=max(maximum, array[i]);
//     }
//   }
//   // We have to divide the array into subarrays
//   else {
//     // Parent inside
//     int M=(L+R)/2;
//     if (fork()) {
//       int first_status;
//       wait(&first_status);
//       int first_max=WEXITSTATUS(first_status);
//       // Parent inside
//       if (fork()) {
//         int second_status;
//         wait(&second_status);
//         int second_max=WEXITSTATUS(second_status);
//         // Now we have the first child maximum as well as second child maximum, take the maximum of both
//         maximum=max(first_max, second_max);
//       }
//       // Second child inside
//       else {
//         int second_child_maximium=merge_maximum(M+1, R, array);
//         exit(second_child_maximium);
//       }
//     }
//     // First child inside
//     else{
//       int first_child_maximum=merge_maximum(L, M, array);
//       exit(first_child_maximum);
//     }
//   }
//   return maximum;
// }
//
// int main(int argc, char *arg[]) {
//   srand(time(NULL));
//   int n=atoi(arg[1]); /* Passed the size of array */
//   int *array=malloc(n*sizeof(int));
//   for (int i=0;i<n;++i) {
//     // Considering we have positive values only in the array
//     array[i]=rand()%36; /* Random numbers from 0-35*/
//   }
//   for (int i=0;i<n;++i) {
//     printf("%d ", array[i]);
//   }
//   printf("\n");
//
//   int maximum=merge_maximum(0, n-1, array);
//   printf("The maximum in the array: %d\n", maximum);
//   return 0;
// }