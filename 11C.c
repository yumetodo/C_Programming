#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 10000
struct student {
  int id;
  char account[9];
};

void set(struct student* s, int id, char *account);
void swap(struct student *x,struct student *y);
void insert(struct student *a, int n, struct student v);

int main(void) {
#define BUFSIZE 80
  struct student *students, v;
  char buf[BUFSIZE], *account;
  int nstudents;    /* 読み込んだ学生の数 */
  int i, len, id;
  /* LIMIT 件分の配列を確保 */
  students = (struct student*) malloc(sizeof(struct student) * LIMIT);
  /* 読み込み */
  for (nstudents = 0; nstudents < LIMIT; nstudents++) {
    if (fgets(buf, sizeof(buf), stdin) == NULL)
      break; /* 入力の終わりで抜ける */
    len = strlen(buf);
    if(buf[len - 1] == '\n')
      buf[len - 1] = '\0';
    /* 行末の改行文字を消す */
    buf[7] = '\0';
    id = atoi(buf);
    account = buf + 8;
    while (*account == ' ')
      account++;
    set(&v, id, account);
    insert(students, nstudents, v);
    /**/
//    printf("[data]\n");
//    for (i = 0; i <= nstudents; i++)
//      printf("%7d %s\n", students[i].id, students[i].account);
    /**/
  }
  /* 表示 */
  for (i = 0; i < nstudents; i++)
    printf("%7d %s\n", students[i].id, students[i].account);
  
  return 0;
}

void set(struct student* s, int id, char *account) {
  s->id = id;
  strcpy(s->account, account);
}

void swap(struct student *x,struct student *y){
  struct student tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void insert(struct student *a,int n,struct student v){
  int i;
  for(i = 0; i < n; i += 1) {
    if(a[i].id > v.id)
      swap(&v, &a[i]);
  }
  a[i] = v;
}
