#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 78

struct stack {
  int top;
  char data[LEN / 2];
};

void push(struct stack *s, char c);
char pop(struct stack*s);
char pare(char str);

int main(void) {
  char str[LEN + 2];
  char *ps;
  struct stack st;
  ps = str;
  st.top = -1;

  fgets(str, sizeof(str), stdin);
  while (*ps != '\0') {
    /* 開き括弧が現れたら stack に期待される閉じ括弧を push する */
    if (*ps == '(')
      push(&st, ')');
    if (*ps == '{')
      push(&st, '}');
    /* 閉じ括弧が適切であるかの判定 */
    if (*ps == ')') {
      /* stack が空の場合は no を出力する */
      if (st.top == -1) {
        printf("no\n");
        /* 処理を終了する */
        return 0;
      }
      /* 適切で無い閉じ括弧が現れた場合は no を出力する */
      else if (pop(&st) == '}') {
        printf("no\n");
        /* 処理を終了する */
        return 0;
      }
    }
    /* 閉じ括弧が適切であるかの判定 */
    if (*ps == '}') {
      /* stack が空の場合は no を出力する */
      if (st.top == -1) {
        printf("no\n");
        /* 処理を終了する */
        return 0;
      }
      /* 適切で無い閉じ括弧が現れた場合は no を出力する */
      else if (pop(&st) == ')') {
        printf("no\n");
        /* 処理を終了する */
        return 0;
      }
    }
    ps += 1;
  }
  if (st.top == -1)
    printf("yes\n");
  else
    printf("no\n");

  return 0;
}

void push(struct stack *s, char c) {
  s->top += 1;
  if (s->top >= LEN) {
    exit(1);
  } else {
    s->data[s->top] = c;
  }
}

char pop(struct stack *s) {
  char c;
  if (s->top < 0) {
    exit(1);
  } else {
    c = s->data[s->top];
    s->top -= 1;
    return c;
  }
}

