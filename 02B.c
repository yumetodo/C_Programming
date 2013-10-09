#include <stdio.h>

int main(void) {
  int m, n, tmp;
  /* m, n をそれぞれ読み込む */
  scanf("%d %d", &m, &n);
  /* ユークリッドの互除法を用いて最大公約数を求める */
  if(m < n) {
    tmp = m;
    m = n;
    n = tmp;
  }
  while(n != 0) {
    tmp = n;
    n = m % n;
    m = tmp;
  }
  printf("%d\n", m);
  
  return 0;
}
