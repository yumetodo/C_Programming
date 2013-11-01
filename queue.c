#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef char elemtype;

struct queue{
  int head, tail;
  elemtype elem[SIZE];
};

void enqueue(struct queue *q, elemtype val){
  /* queue の後ろからデータを格納していく */
  q->elem[q->tail] = val;
  /* tail の値を更新する */
  q->tail++;
  /* tail が配列の最後まで進んだ場合は tail を 0 にする (ring buffer) */
  if(q->tail >= SIZE){
    q->tail = 0;
  }
  /* tail と head が一致した場合は処理を終了する */
  if(q->tail == q->head){
    printf("queue overflow\n");
    exit(1);
  }
}

elemtype dequeue(struct queue *q){
  elemtype val;
  /* head と tail の値が一致した場合、処理を終了する */
  if(q->head == q->tail){
    printf("queue underflow\n");
    exit(1);
  }else{
    /* val に queue の先頭のデータを代入する */
    val = q->elem[q->head];
    /* head の値を更新する */
    q->head++;
    /* head が配列の最後まで進んだ場合、head を 0 にする (ring buffer) */
    if(q->head >= SIZE){
      q->head = 0;
    }
    return val;
  }
}

void initqueue(struct queue *q){
  /* head と tail を 0 で初期化する */
  /* はじめに tail に 0 が代入されてそれをまるごと head に代入する */
  q->head = q->tail = 0;
}

int queueempty(struct queue *q){
  /*  */
  return q->head == q->tail;
}

int main(void){
  struct queue num, alp;
  elemtype e;

  initqueue(&num);
  initqueue(&alp);

  while(scanf("%c", &e) != EOF){
    if(e >= '0' && e <= '9'){
      enqueue(&num, e);
    }else{
      enqueue(&alp, e);
    }
  }

  /* print the contents of num */
  printf("num: ");
  while(!queueempty(&num)){
    printf("%c ", dequeue(&num));
  }
  printf("\n");

  /* print the contents of alp */
  printf("alp: ");
  while(!queueempty(&alp)){
    printf("%c ", dequeue(&alp));
  }
  printf("\n");

  return 0;
}
