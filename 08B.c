#include <stdio.h>
#include <stdlib.h>

struct node {
  char elem;
  struct node *next;
};

struct node *initlist();
void insert(struct node *p, char x);
void printlist(struct node *p);

int main(void) {
  struct node *list;
  list = initlist();

  while(1) {
    char tmp = getchar();
    if(tmp == '\n')
      break;
    insert(list, tmp);
  }
  printlist(list);

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
  struct node *n, *t;
  n = (struct node *)malloc(sizeof(struct node));
  t = p;
  n->elem = x;
  n->next = NULL;
  while(t->next != NULL)
    t = t->next;
  t->next = n;
}

void printlist(struct node *p) {
  struct node *n;
  n = p;
  while(n->next != NULL) {
    printf("%c", n->next->elem);
    n->next = n->next->next;
  }
  printf("\n");
}
