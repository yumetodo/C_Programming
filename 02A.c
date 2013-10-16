#include <stdio.h>                                                              
#define N 10 /* 整数の個数の定義 */
int a[N];    /* 整数を読み込む配列 */
int main(void) {
  int i;
  int max;      /* 配列内で最も大きな整数 */
  int semi_max; /* 配列内で2番目に大きな整数 */
  /* 読み込み */
  for (i = 0; i < N; i ++) 
    scanf("%d", &a[i]);
  /* 最大値を判定する */
  max = a[0];
  for (i = 1; i < N; i ++) {
    if (max <= a[i]) {
      semi_max = max;
      max = a[i];
    } else if(semi_max <= a[i]) {
      semi_max = a[i];
    }   
  }
  /* semi_max を出力する */
  printf("%d\n", semi_max); /* 出力 */
  
  return 0;
}
