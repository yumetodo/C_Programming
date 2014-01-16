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

int partition(recordtype a[], int l, int r) {
  int i, k;
  recordtype v;
  v = a[l];
  i = l;
  k = r + 1;
  do {
    do {
      i += 1;
      if(i > r) {
        v = a[r];
        swap(&a[l], &a[r]);
        i = l + 1;
      }
    } while(strcmp(a[i].line, v.line) < 0);
    do {
      k -= 1;
    } while(strcmp(a[k].line, v.line) > 0);
    if(i < k)
      swap(&a[i], &a[k]);
  } while(k > i);
  a[l] = a[k];
  a[k] = v;
 
  return k;
}
/* sort 関数の定義 */
void quicksort(recordtype a[], int l, int r) {
  int i;
  if(l < r) {
    i = partition(a, l, r);
    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);
  }
}

void sort(recordtype a[], int n) {
  quicksort(a, 0, n - 1);
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
