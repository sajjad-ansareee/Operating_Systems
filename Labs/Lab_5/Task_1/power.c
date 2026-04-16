int power(int x, int n) {
  int result=1;
  for (int i=0; i<n; ++i) {
    result=result*x;
  }
  return result;
}