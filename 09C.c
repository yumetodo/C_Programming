#include <stdio.h>
#include <stdlib.h>

typedef char elemtype;                /* 構造体に格納するデータの型 */
typedef struct _link{
  elemtype elem;
  struct _link *next;
} * link;                             /* リストの構造体のポインタ */

link init();                          /* リストの初期化 */
void insert_top(link l, elemtype e);  /* 要素を先頭に追加する */
void insert_end(link l, elemtype e);  /* 要素を末尾に追加する */
void delete(link l);                  /* 引数の次の要素をリストから外す */
void print(link l);                   /* リストの要素を先頭から出力する */
int check(link l);                    /* リストが回分かどうかを判定する */

int main(void) {
  link list;      /* 文字リスト */
  list = init();  /* 初期化 */
  /* 端末から文字列を入力する */
  while(1) {
    int tmp = getchar();
    if(tmp == '\n') /* 改行まで読み込む */
      break;
    /* リストに格納する */
    insert_top(list, tmp);
  }
  /* 関数 check を用いて回分判定を行い、結果を出力する */
  if(list->next == NULL)
    printf("1\n");
  else
    printf("%d\n", check(list));

  return 0;
}

link init() {
  link l;
  l = (link)malloc(sizeof(*l));
  l->next = NULL;
  
  return l;
}

void insert_top(link l, elemtype e) {
  link m, n;
  m = (link)malloc(sizeof(*m));
  n = l;
  m->elem = e;
  m->next = NULL;
  while(n->next != NULL)
    n = n->next;
  n->next = m;
}

void insert_end(link l, elemtype e) {
  link m;
  m = (link)malloc(sizeof(*m));
  m->elem = e;
  m->next = l->next;
  l->next = m;
}

void delete(link l) {
  if(l->next != NULL)
    l->next = l->next->next;
}

void print(link l) {
  link p = l->next;
  while(p != NULL) {
    putchar(p->elem);
    p = p->next;
  }
  putchar('\n');
}

int check(link l) {
  int judge = 1;
  link keep, tmp;
  l = l->next;  /* ダミーヘッダーから一つ進める */ 
  while(l->next != NULL) {
    keep = l->next;
    tmp = keep;
    while(l->next->next != NULL) {
      tmp = l->next;
      delete(l);
    }
    keep->next = NULL;
    if(l->elem == l->next->elem) {
      judge = 1;
    } else {
      judge = 0;
      break;
    }
    l = keep;
  }
  return judge;
}

//int check(link l) {
//  link m, n;     /* l を逆から読み込むリスト */
// m = init();
//  n = l->next;
//  /* リスト m にリスト l の要素を末尾から追加していく */
//  while(n != NULL) {
//    insert_end(m, n->elem);
//    n = n->next;
//  }
//  /* それぞれポインタを一つ進める */
//  l = l->next;
//  m = m->next;
//  /* 逆から読んでも同じかどうか比較する */
//  while(l != NULL && m != NULL) {
//    if(l->elem == m->elem) {
//      /* 一致していれば次の文字へ移る */
//     l = l->next;
//      m = m->next;
//    } else {
//      /* 一致しなければ 0 を返す */
//      return 0;
//    }
//  }
//  /* すべて一致する場合は 1 を返す */
//  return 1;
//}
