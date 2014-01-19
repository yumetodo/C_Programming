#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 10000
struct student {
  char account[9];
  int score;
};

void swap(struct student *x,struct student *y);
void insert(struct student* a, int n, struct student v);

int main(void) {
#define BUFSIZE 80
  char buf[BUFSIZE];
  struct student *students, v;
  int nstudents, i;

#define LIMIT 10000
  students = (struct student*)malloc(sizeof(struct student) * (LIMIT + 1));

  for(nstudents = 0; nstudents <= LIMIT; nstudents += 1) {
    if(fgets(buf, sizeof(buf), stdin) == NULL)
      break;
    buf[8] = '\0';
    strcpy(v.account, buf);
    v.score = atoi(buf + 9);
    insert(students, nstudents, v);
  }
  for (i = 1; i <= nstudents; i++)
    printf("%s %d\n", students[i].account, students[i].score);
  
  return 0;
}

void swap(struct student *x,struct student *y){
  struct student tmp;
  tmp = *x;
  *x = *y;
  *y = tmp;
}

void insert(struct student *a,int n,struct student v){
  int i;

  for(i = 1; i <= n; i += 1) {
    if(a[i].score < v.score)
      swap(&v, &a[i]);
  }
  a[i] = v;
  for(i = 1; i <= n; i += 1) {
    if(a[i].score == a[i + 1].score) {
      if(strcmp(a[i].account, a[i + 1].account) > 0)
        swap(&a[i], &a[i + 1]);
    }
  }
  
}
