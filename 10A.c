#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 80

typedef char* elementtype;
typedef struct node {
  elementtype element;
  struct node *next;
} *link;
typedef link list;
typedef link position;

list initlist();
position first(list l);
position end(list l);
position next(list l, position p);
void printlist(list l);
void insert(list l, position p, elementtype e);
elementtype retrieve(list l, position p);

int main(void) {
  list music;
  music = initlist();
  
  while(1) {
    char buf[MAXLENGTH + 2];
    fgets(buf, sizeof(buf), stdin);
    if(buf[0] == '.')
      break;
    insert(music, end(music), buf);
  }

  printlist(music);

  position del, dnext;
  dnext = first(music);

  while(dnext) {
    del = dnext;
    dnext = next(music, dnext);
    free(dnext);
  }

  return 0;
}

list initlist() {
  list l;
  l = (list)malloc(sizeof(*l));
  l->next = NULL;

  return l;
}

position first(list l) {
  return l;
}

position end(list l) {
  position p = l;
  while(p->next != NULL) {
    p = next(l, p);
  }
  
  return p;
}

position next(list l, position p) {
  return p->next;
}

void printlist(list l) {
  position p = l->next;
  while(p != NULL) {
    printf("%s", p->element);
    p = next(l, p);
  }
}

void insert(list l, position p, elementtype e) {
  position n;
  n = (position)malloc(sizeof(*n));
  n->element = (elementtype)malloc(sizeof(char) * (MAXLENGTH + 2));
  n->element = strdup(e);
  n->next = p->next;
  p->next = n;
}

elementtype retrieve(list l, position p) {
  return p->element;
}
