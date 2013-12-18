#include <stdio.h>
#include <stdlib.h>

typedef char elemtype;
typedef struct _link {
  elemtype elem;
  struct _link *next;
} * link;

link init();
void insert(link l, elemtype e);
void delete(link l);
void pair(link l);
void print(link l);

int main(void) {
  link list = init();

  while(1) {
    int tmp = getchar();
    if(tmp == '\n')
      break;
    insert(list, tmp);
  }
  pair(list);
  print(list);
  return 0;
}

link init() {
  link l;
  l = (link)malloc(sizeof(*l));
  l->next = NULL;
  return l;
}

void insert(link l, elemtype e) {
  link m, n;
  m = (link)malloc(sizeof(*m));
  n = l;
  m->elem = e;
  m->next = NULL;
  while(n->next != NULL)
    n = n->next;
  n->next = m;
}

void delete(link l) {
  if(l->next != NULL)
    l->next = l->next->next;
}

void pair(link l) {
  link m, n, oldm, oldn;
  m = l->next;
  n = NULL;
  oldm = l;
  while(m != NULL && m->next != NULL) {
    if(n != NULL && n->elem == m->elem)
      break;
    n = m->next;
    oldn = m;
    link tmpn = NULL;
    while(n != NULL) {
      if(n->elem == m->elem) {
        tmpn = oldn;
        break;
      }
      oldn = n;
      n = n->next;
    }
    if(tmpn != NULL) {
      delete(tmpn);
      delete(oldm);
      m = m->next;
    } else {
      oldm = m;
      m = m->next;
    }
  }
}

void print(link l){
  link p = l->next;
  while(p != NULL) {
    putchar(p->elem);
    p = p->next;
  }
  putchar('\n');
}
