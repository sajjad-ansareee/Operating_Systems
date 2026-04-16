
#include "stdio.h"
int cube(int a);
int power(int a, int b);
int square(int x);

int main() {
  printf("Square:%d\n", cube(3));
  printf("Power:%d\n", power(3, 3));
  printf("Square:%d\n", square(5));
  return 0;
}