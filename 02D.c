#include <stdio.h>
#include <stdlib.h>
#define N 3       /* 行列のサイズ */
#define M 4       /* 行列のベキ指数 */
#define BUFLEN 100

float m[N][N];    /* 読み込んだ行列 */
char buf[BUFLEN]; /* 1行を読み込む行列 */

void matrix(float a[N][N], float b[N][N], float c[N][N]);

int main(void) {
  int r, c, i, j;
  float ans[N][N];  /* 乗算した行列 */
  int exp = M;      /* 行列のベキ指数 */
  /* 読み込み */
  for (r = 0; r < N; r ++) {
    char* p = fgets(buf, sizeof(buf), stdin);
    for(c = 0; c < N; c ++)
      m[r][c] = strtof(p, &p);
  }
  /* 結果を単位行列に初期化する */
  for (i = 0; i < N; i ++) {
    for (j = 0; j < N; j ++) {
      if (i != j)
        ans[i][j] = 0;
      else
        ans[i][j] = 1.0;
    }
  }
  
  /* 関数 matrix を用いて行列を M 乗する */
  while (exp != 0) {
    if (exp & 1)
      matrix (ans, m, ans);
    exp = exp >> 1;
    matrix (m, m, m);
  }
  /* 出力 */
  for (r = 0; r < N; r ++){
    for(c = 0; c < N; c ++) {
      if (c > 0)
        printf(" ");
      printf("%f", ans[r][c]);
    }
    printf("\n");
  }
  return 0;
}

void matrix(float a[N][N], float b[N][N], float c[N][N]) {
  int i, j, k;
  float d[N][N];

  /* 結果を零行列に初期化する */
  for (i = 0; i < N; i ++)
    for (j = 0; j < N; j ++)
      d[i][j] = 0.0;

  for (i = 0; i < N; i ++)
    for (j = 0; j < N; j ++)
      for (k = 0; k < N; k ++)
        d[i][j] += a[i][k] * b[k][j];

  for (i = 0; i < N; i ++)
    for (j = 0; j < N; j ++)
      c[i][j] = d [i][j];
}
