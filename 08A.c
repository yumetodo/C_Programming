#include <stdio.h>
#include <stdlib.h>

struct node{
  char elem;
  struct node *next;
};

struct node *initlist();
void insert(struct node *n, char c);
void printlist(struct node *p);

int main(void) {
  struct node *list;
  list = initlist();
  char tmp, *pt;
  pt = &tmp;
  /* 要素をリストに格納 */
  while(1) {
    *pt = getchar();
    if(*pt == '\n')
      break;
    insert(list, *pt);
  }
  /* 出力 */
  printlist(list);
  putchar('\n');

  free(list);
  return 0;
}

struct node *initlist() {
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node));
  n->next = NULL;
  return n;
}

void insert(struct node *p, char x) {
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node));
  n->elem = x;
  n->next = p->next;
  p->next = n;
}

void printlist(struct node *p) {
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node));
  n = p;

  /* list の内容を先頭から出力 */
  if(n->next == NULL) {
    printf("\n");
  } else {
    printf("%c", n->next->elem);
    printlist(n->next);
    /* list の内容を末尾から出力 */
    printf("%c", n->next->elem);
  }
}
