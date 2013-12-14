#include <stdio.h>
#define N 450000
/* 再帰関数 */
int fact1(int n, int a);
double xn1(double x, int n, double a);
/* 非再帰関数 */
int fact2(int n, int a);
double xn2(double x, int n, double a);

int main(void) {
  double x = 0.5;
  int n = 30;
  int i, j;
  double ans;
  
  for(i = 0; i < N; i ++) {
    ans = 0;
    for(j = 0; j < n; j ++) {
      ans += xn1(x, j, 1) / fact1(j, 1);
    }
  }
  printf("%f\n", ans);
  return 0;
}

int fact1(int n, int a) {
  if(n <= 1)
    return a;
  else
    return fact1(n - 1, a * n);
}

double xn1(double x, int n, double a) {
  if(n == 0)
    return a;
  else
    return xn1(x, n - 1, a * x);
}

int fact2(int n, int a) {
  int i;
  for(i = 1; i <= n; i ++)
    a *= i;
  return a;
}

double xn2(double x, int n, double a) {
  int i;
  for(i = 1; i <= n; i ++)
    a *= x;
  return a;
}
