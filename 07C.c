#include <stdio.h>

int divide3(int n);

int main(void) {
  int n;

  scanf("%d", &n);

  printf("%d\n", divide3(n));

  return 0;
}

int divide3(int n) {
  if(n == 0 || n == 1)
    return 0;
  else if(n == 2)
    return 1;
  else
    return divide3(n - 1) * 2 * (2 * n - 5) / (n - 1);
}
