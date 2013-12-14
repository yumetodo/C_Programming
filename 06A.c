#include <stdio.h>

int combination(int n, int m);

int main(void) {
  int n, m;
  /* ２つの整数を読み込む */
  scanf("%d %d", &n, &m);
  /* 出力する */
  if(n < m)
    printf("0\n");
  else
    printf("%d\n", combination(n, m));

  return 0;
}

int combination(int n, int m) {
  if (n == m) {
    return 1;
  } else if(m == 0) {
    return 1;
  } else if(m == 1) {
    return n;
  } else {
    return (combination(n - 1, m - 1) + combination(n - 1, m));
  }
}
