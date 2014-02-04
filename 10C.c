#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 80

typedef char* elementtype;
typedef struct node {
  elementtype element;
  struct node *next, *prev;
} *link;
typedef link list;
typedef link position;

list initlist();
position first(list l);
position end(list l);
position next(list l, position p);
void printlist(list l);
void insert(list l, position p, elementtype e);
elementtype retrieve(list l, position p);
position lseek(list l, int num);       /* リスト l の先頭から num 番目の位置を返す */
position previous(list l, position p); /* リスト l 内の位置 p をの直前の要素の位置を返す */
void delete(list l, position p);       /* リスト l の位置 p の要素を削除する */

int main(void) {
  list music;
  position pn, rn, dn, mn, nn;  /* コマンド用ポインタ */
  char cmd;                     /* p, r, d, m, q のいずれかのコマンド */
  int cn1, cn2;                 /* コマンドの引数 */
  int i;                        /* カウンター */
  music = initlist();

  while(1) {
    char buf[MAXLENGTH + 2];
    fgets(buf, sizeof(buf), stdin);
    if(buf[0] == '.')
      break;
    insert(music, end(music), buf);
  }
//  printf("[List]\n");
//  printlist(music);
  /* コマンド操作 */
  while(1) {
    /* コマンド入力 */
    scanf("%c %d %d", &cmd, &cn1, &cn2);
    /* コマンドごとの動作 */
    if(cmd == 'p') {
      if(lseek(music, cn1) != NULL && cn1 <= cn2) {
        /* 先頭を cn1 まで移動する */
        pn = lseek(music, cn1);
        /* 要素を出力していく */
        for(i = cn1; i <= cn2; i += 1) {
          printf("%s", pn->element);
          pn = next(music, pn);
        }
      } 
    }
   else if(cmd =='r') {
      if(cn1 >= cn2) {
        /* 先頭を cn1 まで移動する */
        /* cn1 が要素数よりも多い場合は調整する */
        if(lseek(music, cn1) == NULL) {
          rn = end(music);
          i = 1;
          while(lseek(music,i) != NULL)
            i += 1;
          cn1 = i - 1;
        }
        else {
          rn = lseek(music, cn1);
        }
        /* 要素を出力していく */
        while(cn1 >= cn2) {
          printf("%s", rn->element);
          if(cn1 != 1)
            rn = previous(music, rn);
          cn1 -= 1;
        }
      }
    }
    else if(cmd == 'd') {
      if(cn2 == 0)
        ;
      else if(lseek(music, cn2) != (position)0) {
        dn = lseek(music, cn2);
        if(dn->element == NULL)
          ;
        else
          delete(music, dn);
      }
      printlist(music);
    }
    else if(cmd == 'm') {
      if(lseek(music, cn1) != NULL && lseek(music, cn2) != NULL) {
        position tmp1, tmp2;
        /*
         * a b c d e
         *   |   |   
         *   m   n    
         *
         */
        mn = lseek(music, cn1);
        nn = lseek(music, cn2);
        tmp1 = mn->prev;        
        tmp2 = nn->prev;

//        tmp1->next = nn;
//        tmp2->next = mn;

        insert(music, previous(music, mn), retrieve(music, nn));
        insert(music, previous(music, nn), retrieve(music, mn));
        delete(music, mn);
        delete(music, nn);
//        tmp1 = nn->next;
//        nn->next = mn->next;
//        mn->next = tmp1;
      }
      printlist(music);
    }
    else if(cmd == 'q') {
      break;
    }
  }
//  printlist(music);

  position p, q;
  p = next(music, first(music));
  while(p != music) {
    q = p;
    p = next(music, p);
    free(p);
  }

  return 0;
}

list initlist() {
  list l;
  l = (list)malloc(sizeof(*l));
  l->next = l->prev = l;

  return l;
}

position first(list l) {
  return l;
}

position end(list l) {
  position p = l->prev;
  return p;
}

position next(list l, position p) {
  return p->next;
}

void printlist(list l) {
  position p = next(l, first(l));
  while(p->element != NULL) {
    printf("%s", p->element);
    p = next(l, p);
  }
}

void insert(list l, position p, elementtype e) {
  /*
   * ... -> p -> x -> ...
   * ... <- p <- x <- ...
   */
  position n, m;
  m = next(l, p);
  n = (position)malloc(sizeof(*n));
  n->element = (elementtype)malloc(sizeof(char) * (MAXLENGTH + 2));
  n->element = strdup(e);
  /*
   * ... -> p -> o -> ...
   * ... <- p <- o <- ...
   */
  n->next = p->next;
  p->next = n;
  /*
   * ... -> p -> n -> o -> ... 
   * ... <- p    n    o <-
   *        ^
   *        |         |
   *        -----------
   */
  n->next->prev = n;
  n->prev = p;
  /*
   * ... -> p -> n -> o -> ...
   * ... <- p <- n <- o <- ...
   */
}

elementtype retrieve(list l, position p) {
  return p->element;
}

position lseek(list l, int num) {
  position p = next(l, first(l));  /* リストの1番目 */
  int i;
  for(i = 1; i < num; i += 1) {
    p = next(l, p);
    if(p == first(l))
      return (position)0;
  }

  return p;
}

position previous(list l, position p) {
  return p->prev;
}

void delete(list l, position p) {
  position q, r;
  q = previous(l, p);
  r = next(l, p);

  q->next = r;
  r->prev = q;

  free(p);
}
