#include <stdio.h>
int v[2] = {31, 31 * 63 + 15};

int fiv(int n) {
  int a;
  int b;
  /* この時点の様子１ */
  if (n <= 1) {
    return v[n];
  } else {
    a = fiv(n - 1);
    /* この時点の様子２ */
    b = fiv(n - 2);
    /* この時点の様子３ */
    /**/
    printf("a : %d\n", a);
    printf("b : %d\n", b);
    /**/
    return a + b;
  }
}

int ss(int n) {
  int m;
  /* この時点の様子１ */
  if (n < 2) {
    return n;
  } else {
    m = ss(n-1);
    /* この時点の様子２ */
    return n*n + m;
  }
}
int main(void) {
  
  printf("%d\n", fiv(3));
  
  return 0;
}
