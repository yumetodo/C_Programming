#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 10000
typedef struct {
  int n;
} recordtype;

recordtype a[LIMIT];

void swap(recordtype *x, recordtype *y);
void pushdown(recordtype *b, int first, int last);
void heapsort(recordtype *r, int n);

int main(void) {
#define BUFLEN 16
  char buf[BUFLEN];
  int i, n;

  for(n = 0; n < LIMIT; n += 1) {
    if(fgets(buf, sizeof(buf), stdin) == NULL)
      break;
    a[n].n = atoi(buf);
  }
  heapsort(a, n);
  for(i = 0; i < n; i += 1)
    printf("%d\n", a[i]);

  return 0;
}

void swap(recordtype *x, recordtype *y) {
  recordtype tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void pushdown(recordtype* b, int first, int last) {
  int r = first;
  int k = r * 2;
  while(k <= last) {
    if(k < last && b[k].n < b[k + 1].n)
      k += 1;
    if(b[r].n >= b[k].n)
      break;
    swap(&b[r], &b[k]);
    r = k;
    k = r * 2;
  }
}

void heapsort(recordtype* r, int n) {
  int i;
  for(i = n / 2 - 1; i >= 0; i -= 1)
    pushdown(r, i, n);
  for(i = n - 1; i >= 1; i -= 1) {
    swap(&a[0], &a[i]);
    pushdown(r, 0, i - 1);
  }
}
/*
void heapsort(recordtype* r, int n) {
  int i;
  for(i = n / 2; i >= 1; i -= 1)
    pushdown(r, i, n);
  for(i = n; i >= 2; i -= 1) {
    swap(&a[1], &a[i]);
    pushdown(r, 1, i - 1);
  }
}
*/
