#include <stdio.h>
#include <string.h>

#define LIMIT 10000  /* 最大行数 */
#define MAX_LEN 80   /* 行の長さの上限 */
typedef struct {
  char* line;
} recordtype;

recordtype text[LIMIT];

void swap(recordtype *x, recordtype *y) {
  recordtype temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

/* sort 関数の定義 */
void sort(recordtype a[], int n) {
  int i, j, minindex;

  for(i = 0; i < n - 1; i += 1) {
    minindex = i;
    for(j = i + 1; j <= n - 1; j += 1) {
      if(strcmp(a[j].line, a[minindex].line) < 0)
        minindex = j;
    }
//    printf("a[%d](%s) <-> a[%d](%s)\n",
//        i, a[i].line, minindex, a[minindex].line);
    swap(&a[minindex], &a[i]);
  }
}

int main() {
  int i, len;
  int nlines;  /* 読み込んだ行数 */
  char buf[MAX_LEN + 2];
  /* 読み込み */
  for(nlines = 0; nlines < LIMIT; nlines += 1) {
    if(fgets(buf, sizeof(buf), stdin) == NULL)
      break;                                    /* 入力の終りで抜ける */
    len = strlen(buf);
    if(buf[len - 1] == '\n')
      buf[len - 1] = '\0';                      /* 行末の改行文字を消す */
    text[nlines].line = strdup(buf);
  }
  /* ソート */
  sort(text, nlines);
  /* 表示 */
  for(i = 0; i < nlines; i += 1)
    printf("%s\n", text[i].line);

  return 0;
}
