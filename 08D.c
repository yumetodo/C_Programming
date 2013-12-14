#include <stdio.h>
#include <stdlib.h>
typedef struct _link {
  char elem;
  struct _link *next;
} link;

link *initlist();
void insert(link *n, char x);
void delete(link *n);
void printlist(link *n);
void sortlist(link *n);

int main(void) {
  link *list, *tmp, *p, *oldp;
  list = initlist();
  while(1) {
    int ch = getchar();
    if(ch == '\n')
      break;
    insert(list, ch);
  }
  printlist(list);

  sortlist(list);
  printlist(list);

  free(list);
  return 0;
}

link *initlist() {
  link *n;
  n = (link *)malloc(sizeof(link));
  n->next = NULL;
  return n;
}

void insert(link *n, char x) {
  link *p, *q;
  p = (link *)malloc(sizeof(link));
  q = n;
  p->elem = x;
  p->next = NULL;
  while(q->next != NULL)
    q = q->next;
  q->next = p;
}

void delete(link *n) {
  if(n->next != NULL)
    n->next = n->next->next;
}

void printlist(link *n) {
  link *p;
  p = n->next;
  while(p != NULL) {
    printf("%c", p->elem);
    p = p->next;
  }
  printf("\n");
}

void sortlist(link *n) {
  link *p, *oldp, *tmp;
  int count;
  p = n->next;
  /* リストの要素数を数える */
  for(count = 0; p != NULL; count ++) {
    p = p->next;
    count += 1;
  }
  oldp = n;  
  p = n->next;
  /*
   * カウントが0になるまで処理をする
   * a : そのまま隣に移行する
   * b : ポインタを結び変えて末尾に持ってくる
   */
  while(p != NULL && count != 0) {
    if(p->elem == 'a') {
      oldp = p;
      p = p->next;
    } else {
      tmp = p;
      delete(oldp);
      p = p->next;
      insert(p, tmp->elem);
 //     p = p->next;
    }
    count -= 1;
  }
}
