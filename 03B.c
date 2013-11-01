#include <stdio.h>
#define LEN 78

int strlen(char *s1);
char *findhead(char *s1, char *s2);

int main(void) {
  char s1[LEN + 2];
  char s2[LEN + 2];
  char *ps1, *ps2, *head;  /* 文字列のポインタ */
  char *hps1, *hps2;       /* 文字列の先頭アドレスを格納するポインタ */
  /* 文字列を読み込む */
  fgets(s1, sizeof(s1), stdin);
  fgets(s2, sizeof(s2), stdin);
  /* 文字列の先頭アドレスをポインタに格納する */
  hps1 = s1;
  hps2 = s2;
  /* 文字列の行末の改行を'\0'に変換する */
  ps1 = s1;
  ps2 = s2;
  while(*ps1 != '\0') {
    if(*ps1 == '\n')
      *ps1 = '\0';
    ps1 += 1;
  }
  while(*ps2 != '\0') {
    if(*ps2 == '\n')
      *ps2 = '\0';
    ps2 += 1;
  }
  /* 関数 findhead を用いて文字列の探索を行う */
  head = findhead(s1, s2);
  /* 結果を出力する */
  if(head == NULL)
    printf("\n");
  else
    printf("%s\n", head);

  return 0;
}

int strlen(char *s1) {
  int len = 0;
  while (*s1 != '\0') {
    len += 1;
    s1 += 1;
  }
  return len;
}
char *findhead(char *s1, char *s2) {
  char *fps1 = s1;
  char *fps2 = s2;
  char *fhps2 = s2; /* s2 の先頭アドレスを格納するポインタ */
  char *head = 0;   /* 一致部分の先頭を格納するポインタ NULL で初期化する */
  /* s2 と s1 に一致する部分があるか探索する */
  while(*fps1 != '\0' || *fps2 != '\0') {
    if(*fps2 == *fps1) {
      /* 双方の文字が一致した場合はそれぞれ隣の文字へ移行する */
      fps1 += 1;
      fps2 += 1;
      if(*fps2 == '\0')
      return (fps1 - strlen(s2));
    } else {
      /* 一致しなかった場合、s1 は隣の文字へ、s2は先頭へ移行する */
      fps1 += 1;
      fps2 = fhps2;
    }
  }
  return NULL;
}
