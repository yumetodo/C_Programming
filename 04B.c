#include <stdio.h>
#include <stdlib.h>
#define QUEUESIZE 10
#define BUFSIZE 100
#define N 5
typedef int elemtype;

struct queue{
  int head, tail;
  elemtype elem[QUEUESIZE];
};

void enqueue(struct queue *q, elemtype val);  /* この関数を実装する */
elemtype dequeue(struct queue *q);            /* この関数を実装する */
void initqueue(struct queue *q);              /* この関数を実装する */
int queueempty(struct queue *q);              /* この関数を実装する */
/* 与えられたキューの内容を表示する。*/
void printq(struct queue q) {
  printf("(");
  if (!queueempty(&q)) {
    printf("%d", dequeue(&q));
  while (!queueempty(&q))
    printf(" %d", dequeue(&q));
  }
  printf(")\n");
}

int main(void) {
  struct queue qin, qout;
  char buf[100];
  int i, j, x, y;
  initqueue(&qin);
  initqueue(&qout);
  /* N 個の整数を与えられた順にキュー qin に格納する。*/
  for (i = 0; i < N; i++) {
    enqueue(&qin, atoi(fgets(buf, BUFSIZE, stdin)));
  }
  /* キュー qin に格納された整数を昇順に並び替えて キュー qout に格納する。*/
  for (i = 0; i < N; i++) {
    x = dequeue(&qin);
    for (j = i; j < N - 1; j++) {
      y = dequeue(&qin);
      if(x < y){
        enqueue(&qin, y);
      } else {
        /* x の値を y に置き換える */
        enqueue(&qin, x);
        x = y;
      }
    }
    enqueue(&qout, x);
  }
  printq(qout);
  return 0;
}

void enqueue(struct queue *q, elemtype val) {
  /* queue の末尾に val を格納する */
  q->elem[q->tail] = val;
  /* tail の値を更新する */
  q->tail += 1;
  /* tail がサイズの大きさに達したら先頭に戻す */
  if (q->tail >= QUEUESIZE)
    q->tail = 0;
  /* head と tail が等しくなったら処理を終了 */
  if (q->tail == q->head)
    exit(1);
}

elemtype dequeue(struct queue *q) {
  elemtype val;
  /* head と tail が等しくなったら処理を終了 */
  if (q->head == q->tail) {
    exit(1);
  } else {
    /* val に queue の先頭の値を代入 */
    val = q->elem[q->head];
    /* head の値を更新する */
    q->head += 1;
    /* head がサイズの大きさに達したら先頭に戻す */
    if (q->head >= QUEUESIZE)
      q->head = 0;
  }
  return val;
}

void initqueue(struct queue *q) {
  /* queue の head と tail を 0 に戻す */
  q->head = q->tail = 0;
}

int queueempty(struct queue *q) {
  /**/
  return q->head == q->tail;
}
