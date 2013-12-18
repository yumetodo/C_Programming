#include <stdio.h>
#include <stdlib.h>

typedef char elemtype;  /* データの型 */
typedef struct _link {
  elemtype x;
  struct _link *next;
} * link;               /* リストの構造体 */

link initlist();
void insert(link l, elemtype x);
void delete(link l);

int main(void) {
  link list = initlist();
  while(1) {
    /* 入力された文字を読み込む */
    int tmp = getchar();
    /* 改行するまで読み込む */
    if(tmp == '\n')
      break;
    /* 入力した文字をリストに格納する */
    insert(list, tmp);
  }
  return 0;
}
