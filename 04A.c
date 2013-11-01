#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 10   // stackの大きさ
typedef int elemtype;  // stack 要素の型
struct stack{
  int top;
  elemtype elem[STACKSIZE];
};

void initstack( struct stack *s){
  s->top = -1;
}

void push( struct stack *s, elemtype val ){
  s->top += 1;
  s->elem[s->top] = val;
}

elemtype pop(struct stack *s){
  int n;
  n = s->top;

  s->top -= 1;
  return s->elem[n];
}
/* stackの内容を表示する関数 */
void print_stack(struct stack s,char *hint) {
  int p;
  printf("[");
  for (p = 0; p <= s.top; p++) {
    printf("%d", s.elem[p] );
    if (p <= s.top - 1) printf(", ");
  }
  printf("] # %s\n", hint);
}

int main(void) {
  struct stack st;
  int i;
  initstack( &st );
  for (i = 1; i <= 5; i++) {
    push(&st, i);
    print_stack(st, "push 1"); }
  for (i = 0; i < 4; i++) { int x, y;
    x = pop(&st); print_stack(st, "pop 1"); y = pop(&st); print_stack(st, "pop 2"); push(&st, x + y); print_stack(st, "push 2");
  }
  return 0;
}
