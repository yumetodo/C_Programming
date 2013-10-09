#include<stdio.h>
#define N 3

void matrix(double a[N][N], double b[N][N], double c[N][N]);

int main(void) {
	int n;						/* 行列の指数 */
	double mat[N][N];	/* n 乗する行列 */
	double ans[N][N];
	int i = 0, j = 0;	/* カウント用変数 */

	/* 行列の指数を読み込む */
	scanf("%d", &n);
	/* 行列の要素を読み込んでいく */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			scanf("%lf", &mat[i][j]);
		}
	}
	/* 結果を単位行列に初期化する */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			if(i != j) {
				ans[i][j] = 0;
			} else {
				ans[i][j] = 1.0;
			}
		}
	}

	/* 関数 mat を用いて行列を n 乗する */
	while(n != 0) {
		if(n & 1)
			matrix(ans, mat, ans);
		n = n >> 1;
		matrix(mat, mat, mat);
	}

	/* 結果を出力する */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			printf("%.3lf ", ans[i][j]);
		}
		printf("\n");
	}

	return 0;
}

void matrix(double a[N][N], double b[N][N], double c[N][N]) {
	int i, j, k;
	double ans[N][N];

	/* 結果の行列を零行列に初期化する */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			ans[i][j] = 0.0;
		}
	}
	/*  */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			for(k = 0; k < N; k ++) {
				ans[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	/*  */
	for(i = 0; i < N; i ++) {
		for(j = 0; j < N; j ++) {
			c[i][j] = ans[i][j];
		}
	}
}

