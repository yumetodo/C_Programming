#include <stdio.h>
#include <stdlib.h>
#define LEN 78

int check(char *str);

int main(void) {
  char buf[SIZE + 2];
  int judge = 0;

  fgets(buf, LEN, stdin);
}

int check(char *str) {
  
  if (*str == '\0' || *str == '\n')
    return -1;
  else
    return (check(*str + 1));
}
