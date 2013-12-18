#include <stdio.h>
#define LEN 78  /* 文字列の長さ */

/* 括弧が正しく用いられているかどうかの判定を行う関数 */
char *check(int *pi, char *ps);

int main(void) {
  char buf[LEN + 2];  /* 判定する文字列 */
  char *ans;          /* 判定の結果を代入するポインタ */
  int class = 1;      /* 文字列の分類 */
  /* 文字列を読み込む */
  fgets(buf, sizeof(buf), stdin);
  /* 関数checkを用いて判定を行う*/
  ans = check(&class, buf);
  /* 括弧が正しく用いられているならyesを出力する */
  if(class == 1)
    printf("yes\n");
  /* そうでなければnoを出力する */
  else
    printf("no\n");

  return 0;
}

char *check(int *pi, char *ps) {
  char *position = ps;
  /* 文字列の終端まで達したら NULL を返す */
  if(*ps == '\0'){
    return NULL;
  }
  /* 閉じ括弧が現れたらその位置を返す */
  else if(*ps == ')' || *ps == '}') {
    /* 一時的にclassに0を代入しておく */
    *pi = 0;
    return ps;
  }
  /* 開き括弧が現れたら再帰的にcheckを呼び出して閉じ括弧の位置を調べる */
  else if(*ps == '(') {
    position = check(pi, ps + 1);
    /* 閉じ括弧が見つからない場合はclassに0を代入する */
    if(position == NULL) {
      *pi = 0;
      return NULL;
    }
    /* 閉じ括弧が正しいかどうかの判定を行う */
    else if(*position == ')') {
      /* 対応した括弧が用いられているのでclassに1を代入する */
      *pi = 1;
      /* 続きを調べる */
      return check(pi, position + 1);
    } else {
      /* 適切でない括弧なのでclassに0を代入する */
      *pi = 0;
      return NULL;
    }
  }
  else if(*ps == '{') {
    position = check(pi, ps + 1);
    /* 閉じ括弧が見つからない場合はclassに0を代入する */
    if(position == NULL) {
      *pi = 0;
      return NULL;
    }
    if(*position == '}') {
      /* 対応した括弧が用いられているのでclassに1を代入する */
      *pi = 1;
      /* 続きを調べる */
      return check(pi, position + 1);
    } else {
      /* 適切でない括弧なのでclassに0を代入する */
      *pi = 0;
      return NULL;
    }
  }
  /* 括弧以外の文字の場合は文字を一つ進める */
  else {
    return check(pi, ps + 1);
  }
}
