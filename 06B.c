#include <stdio.h>
#include <stdlib.h>
#define N 1000
typedef int elemtype;
/*
 n_C_m = n-1_C_m-1 + n-1_C_m を stack で計算する
 */
struct stack {
  int top;
  elemtype data[N];
};

void push(struct stack *s, int val);
elemtype pop(struct stack *s);
int combination(int n, int m);
//int stackempty(struct stack *s);

int main(void) {
  int n, m;
  int ans;
  struct stack s;

  scanf("%d %d", &n, &m);

  if(n < m) {
    printf("1\n");
    return 0;
  } else {
    ans = combination(n, m);
  }
  printf("%d\n", ans);
  return 0;
}

void push(struct stack *s, int val) {
  s->top += 1;
  if(s->top >= N)
    /* Stack Overflow */
    exit(1);
  else
    s->data[s->top] = val;
}

elemtype pop(struct stack *s) {
  elemtype val;
  if(s->top >= N) {
    /* Stack Underflow */
    exit(1);
  } else {
    val = s->data[s->top];
    s->top -= 1;
  }
  return val;
}

int combination(int n, int m) {
  int ans = 0;
  int a, b;
  struct stack sc;
  sc.top = -1;
  
  /* stack に値を格納する */
  push(&sc, n);
  push(&sc, m);
  /* stack が空になるまでループ */
  while(sc.top != -1) {
    /* b に m を代入 */
    b = pop(&sc);
    /* a に n を代入 */
    a = pop(&sc);
    if(a < b)
      ;
    else if(a == 1 || b == 0)
      ans += 1;
    else if(b == 1)
      ans += a;
    else {
      n = a - 1;
      m = b;
      push(&sc, n);
      push(&sc, m);
      m -= 1;
      push(&sc, n);
      push(&sc, m);
    }
  }
  return ans;
}

