#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 10
/* stack を宣言する */
struct stack{
  int top;              /* stack の先頭を示す数字 */
  int data[STACKSIZE];  /* stack のデータを格納する配列 */
};
/* stack に push でデータを格納する関数 */
void push(struct stack *s, int val);
/* stack から pop でデータを取り出す関数 */
int pop(struct stack *s);
/* stack の内容を表示する関数 */
void print_stack(struct stack s, char *hint);

int main(void) {
  struct stack st;
  int i;
  st.top = -1;      /* st のメンバ top を -1 に初期化する */
  for (i = 1; i <= 5; i ++) {
    push(&st, i);
    print_stack(st, "push 01");
  }
  for (i = 0; i < 4; i ++) {
    int x, y;
    x = pop(&st);
    print_stack(st, "pop 01");
    y = pop(&st);
    print_stack(st, "pop 02");
    push(&st, x + y);
    print_stack(st, "push 02");
  }
  return 0;
}

void push(struct stack *s, int val) {
  /* s->top の値を更新して、s->data に順にデータを入れていく */
  s->top += 1;
  s->data[s->top] = val;
}

int pop(struct stack *s) {
  /* 市場鵺の値を変数 top に代入して返す */
  int top = s->data[s->top];
  s->top -= 1;
  return top;
}

void print_stack(struct stack s, char *hint) {
  int j;
  printf("[");
  for(j = 0; j <= s.top; j ++) {
    printf("%d", s.data[j]);
    if(j <= s.top - 1)
      printf(", ");
  }
  printf("] # %s\n", hint);
}

