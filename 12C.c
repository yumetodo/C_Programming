#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
  char account[9];
  int score[10];
} student;

struct node {
  struct node *next;
  student data;
};

void listsort(struct node *n);

int main() {
#define BUFLEN 1024
  char buf[BUFLEN], *s;
  struct node *list, *p;
  int i, n;

  p = list = (struct node*)malloc(sizeof(struct node));
  while(fgets(buf, sizeof(buf), stdin) != NULL) {
    p = p->next = (struct node*)malloc(sizeof(struct node));
    buf[8] = '\0';
    strcpy(p->data.account, buf);
    s = buf + 9;
    for(i = 0; i < 10; i += 1) {
      while(isspace(*s))
        ++ s;
      for(n = 0; isdigit(*s); ++ s)
        n = n * 10 + (*s - '0');
      p->data.score[i] = n;
    }
  }
  p->next = NULL;
  
  listsort(list);
  for(p = list->next; p; p = p->next) {
    printf("%s", p->data.account);
    for(i = 0; i < 10; i += 1)
      printf("%3d", p->data.score[i]);
    printf("\n");
  }

  return 0;
}


void listsort(struct node *n) {
  int i, j, sum, cmp;
  struct node *l,*m, *minindex, *top = n;
  sum = 0;
  l = top->next;
  m = l->next;
  for(i = 0; i < 10; i += 1)
    sum += l->data.score[i];
  minindex = l;

  while(m != NULL) {
    cmp = 0;
    for(i = 0; i < 10; i += 1)
      cmp += l->data.score[i];
    if(sum == cmp) {
      if(strcmp(l->data.account, m->data.account) > 0) {
        minindex = m;
      }
    }
    if(sum < cmp)
      minindex = m;
  }

}
