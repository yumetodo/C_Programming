#include <stdio.h>
#define N 10
typedef struct {int max; int min;} MMpair;
MMpair maxmin(int data[], int left, int right);

int main(void) {
  int a[N];
  int i;
  MMpair ans;

  for(i = 0; i < N; i ++)
    scanf("%d", &a[i]);

  ans = maxmin(a, 0, N - 1);
  printf("%d %d\n", ans.min, ans.max);

  return 0;
}

MMpair maxmin(int data[], int left, int right) {
  MMpair ma, ml, mr;
  int half = (left + right) / 2;

  if(half == left) {
    if(data[left] > data[left + 1]) {
      ma.min = data[left + 1];
      ma.max = data[left];
    } else {
      ma.min = data[left];
      ma.max = data[left + 1];
    }
  } else {
    ml = maxmin(data, left, half);
    mr = maxmin(data, half + 1, right);
    
    if(ml.min < mr.min)
      ma.min = ml.min;
    else
      ma.min = mr.min;

    if(ml.max < mr.max)
      ma.max = mr.max;
    else
      ma.max = ml.max;
  }

  return ma;
}
