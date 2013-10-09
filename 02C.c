#include <stdio.h>
#include <string.h>
#define MAXLEN 78     /* 文字列の最大長 */
char buf[MAXLEN + 2]; /* 文字列を読み込む配列 */
int main(void) {
  char max_string[] = {'\0'}; /* 最も長い行 */
  int maxlen;
  while (1) {
    int len;
    int i;
    fgets(buf, sizeof(buf), stdin); /* 一行読み込む */
    /* 空行であれば終了 */
    if (buf[0] == '\n' || buf[0] == '\0')
      break;
    /* 文字列中に'#' が含まれる場合は '\0' に置き換える */
    for (i = 0; i < MAXLEN + 2; i ++)
      if(buf[i] == 35) /* '#' は ASCIIコード(10進数)で35 */
        buf[i] = '\0';
    /* 行末に改行 (\n) があれば取り除く */
    len = strlen(buf);
    if (buf[len - 1] == '\n')
      buf[len - 1] = '\0';
    /*  */
    maxlen = strlen(max_string);
    if ((len == maxlen && strcmp(buf, max_string) < 0) || (len > maxlen))
      max_string = buf;
  }
  printf("%s\n", buf);
  printf("%s\n", max_string);
  return 0;
}
