#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 8

typedef struct _stdnum {
  int elem;
  struct _stdnum *next;
} stdnum;

typedef struct _acc {
  char elem[LEN];
  struct _acc *next;
} acc;

stdnum *initnum();
acc *initacc();
void insert_num(stdnum *p, int x);
void insert_acc(acc *p, char s[]);

int main(void) {
  stdnum *num = initnum();
  acc *account = initacc();
  int n, i;
  char s[LEN + 2], tmp[LEN + 2];

  while(1) {
    fgets(tmp, sizeof(tmp), stdin);
    if(tmp[0] == '\n' || tmp[0] == '\0')
      break;
    for(i = 0; i < LEN + 2; i ++) {
      if(tmp[i] == '\n')
        tmp[i] = '\0';
    }
    n = atoi(tmp);
    insert_num(num, n);
  }

  while(1) {
    fgets(s, sizeof(s), stdin);
    if(s[0] == '\n' || s[0] == '\0')
      break;
    for(i = 0; i < LEN + 2; i ++) {
      if(s[i] == '\n')
        s[i] = '\0';
    }
    insert_acc(account, s);
  }

  num = num->next;
  account = account->next;
  while(num != NULL || account != NULL) {
    printf("%d %s\n", num->elem, account->elem);
    num = num->next;
    account = account->next;
  }

  free(num);
  free(account);
  return 0;
}

stdnum *initnum() {
  stdnum *p;
  p = (stdnum *)malloc(sizeof(stdnum));
  p->next = NULL;

  return p;
}

acc *initacc() {
  acc *p;
  p = (acc *)malloc(sizeof(acc));
  p->next = NULL;

  return p;
}

void insert_num(stdnum *p, int x) {
  stdnum *n, *l;
  n = (stdnum *)malloc(sizeof(stdnum));
  l = p;
  n->elem = x;
  n->next = NULL;
  while(l->next != NULL)
    l = l->next;
  l->next = n;
}

void insert_acc(acc *p, char c[]) {
  acc *n, *l;
  n = (acc *)malloc(sizeof(acc));
  l = p;
  strcpy(n->elem, c);
  n->next = NULL;
  while(l->next != NULL)
    l = l->next;
  l->next = n;
}
