#include <stdio.h>
#define N 10 /* 整数の個数の定義 */
int a[N];    /* 整数を読み込む配列 */
int main(void) {
  int i;
  int max;     /* 配列内で最も大きな整数 */
  int max_num; /* 最大値の数値の添字 */
  int b[N -1]; /* 配列 a から最大値を除いた配列 */
  for (i = 0; i < N; i ++) scanf("%d", &a[i]); /* 読み込み */
  /* 最大値を判定する */
  max = a[0];
  for (i = 0; i < N; i ++) {
    if (max <= a[i]) {
      max = a[i];
      max_num = i;
    }
  }
  /* max を除いた配列を読み込む */
  i = 0;
  while (i < N - 1) {  
    if(i == max_num) {
      i ++;
    }
    else {
      b[i] = a[i];
      i ++;
    }
  }
  /* bの最大値を判定する */
  max = b[0];
  for ( i = 0; i < N - 1; i ++) {
    if (max <= b[i])
      max = b[i];
  }
  
  printf("%d\n", max); /* 出力 */
  return 0;
}
