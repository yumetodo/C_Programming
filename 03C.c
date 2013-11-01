#include <stdio.h>
#include <string.h>
#define LEN 9
struct student {
  int id;           /* 学籍番号 */
  char account[LEN];  /* アカウント名 */
};
void set(struct student *s, int id, char *account) {
  int i = 0;
  s->id = id;
  while(i < LEN) {
    s->account[i] = *account;
    account += 1;
    i += 1;
  }
}
struct student *search(struct student students[], int n, int id) {
  int i;
  struct student *ans;
  for(i = 0; i < n; i += 1) {
    if(students[i].id == id) {
      ans = &students[i];
      break;
    } else {
      ans = NULL;
    }
  }
  return ans;
}
int main(void) {
#define BUFSIZE 80
#define STDNT   5
  struct student students[STDNT], *s;
  char buf[BUFSIZE], *account;
  int i, len, id;
  /* 5(STDNT) 人分の学籍番号とアカウント名を読み込み,配列 students にセットする.*/
  for (i = 0; i < STDNT; i++) {
    fgets(buf, sizeof(buf), stdin);
    len = strlen(buf);
    if (buf[len - 1] == '\n')
      buf[len - 1] = '\0';
    buf[7] = '\0';
    id = atoi(buf);
    account = buf + 8;
    while (*account == ' ') {
      account++;
    }
    set(&students[i], id, account); /* ここから set を呼び出している */
  }
  /* 学籍番号が与えられる間,それに対応するアカウント名を表示する.*/
  while (fgets(buf, sizeof(buf), stdin)) {
    if (buf[0] == '\n' || buf[0] == '\0')
      break;
    s = search(students, STDNT, atoi(buf)); /* ここから search を呼び出している */
    if (s == NULL)
      printf("no data\n");
    else
      printf("%s\n", s->account);
  }
  return 0;
}
