#include <stdio.h>
#include <stdlib.h>
#define N 7
#define QUEUESIZE N * N

/* (x,y) 地点とそこまでの距離c を記録する構造体*/
struct cost {
  int x;
  int y;
  int c;
  char d;
};

/* 現在の位置を記憶する queue */
struct queue{
  int head,tail;
  struct cost pos[QUEUESIZE];
};

void enqueue(struct queue *q, struct cost c);
struct cost dequeue(struct queue *q);
/*既に同じ道を通っているか調べる*/
int search(struct queue *q, struct cost c);

int main(void) {
  #define BUFSIZE (N*2)
  char buf[BUFSIZE];
  char maze[N][N];
  int i, j, sx, sy, gx, gy;
  int ans = N*N;
  struct cost pos, up, down, left, right;
  struct queue q;
  q.head = q.tail = 0;

  /* 迷路を読み込み、maze にセットする。*/
  for (i = 0; i < N; i++) {
    fgets(buf, BUFSIZE, stdin);
    for (j = 0; j < N && (buf[j] != '\n' && buf[j] != '\0'); j++) {
      if (buf[j] == 'S') {
	sx = j; sy = i; buf[j] = ' ';
      } else if (buf[j] == 'G') {
	gx = j; gy = i; buf[j] = ' ';
      }
      maze[i][j] = buf[j];
    }
    while (j < N) maze[i][j++] = ' ';
  }

  pos.x = sx;
  pos.y = sy;
  pos.c = 0;
  pos.d = 's';
  enqueue(&q, pos);

  while (1) {
    pos = dequeue(&q);
    if (pos.c == -1)
      break;
    if (pos.x == gx && pos.y == gy) {
      ans=pos.c;
      break;
    } else {
      /* Up */
      if (pos.y > 0 && maze[pos.y - 1][pos.x] == ' ' && pos.d != 'd') {
        up.x = pos.x;
        up.y = pos.y - 1;
        up.c = pos.c + 1;
        up.d = 'u';
        if(search(&q, up) == 0 || (up.x == gx && up.y == gy))
          enqueue(&q, up);
      }
      /* Down */
      if (pos.y < N - 1 && maze[pos.y + 1][pos.x] == ' ' && pos.d != 'u') {
        down.x = pos.x;
        down.y = pos.y + 1;
        down.c = pos.c + 1;
        down.d = 'd';
        if (search(&q, down) == 0 || (down.x == gx && down.y == gy))
          enqueue(&q, down);
      }
      /* Left */
      if (pos.x > 0 && maze[pos.y][pos.x - 1] == ' ' && pos.d != 'r') {
        left.x = pos.x - 1;
        left.y = pos.y;
        left.c = pos.c + 1;
        left.d = 'l';
        if (search(&q, left) == 0 || (left.x == gx && left.y == gy))
          enqueue(&q, left);
      }
      /* Right */
      if (pos.x < N - 1 && maze[pos.y][pos.x + 1] == ' ' && pos.d != 'l') {
        right.x = pos.x + 1;
        right.y = pos.y;
        right.c = pos.c + 1;
        right.d = 'r';
        if (search(&q, right) == 0 || (right.x == gx && right.y == gy))
          enqueue(&q, right);
      }
    }
  }

/* 最短距離を表示する。*/
  if (ans == QUEUESIZE)
    ans = -1;
  printf("%d\n", ans);
  return 0;
}

void enqueue(struct queue *q, struct cost c) {
  q->pos[q->tail] = c;
  q->tail += 1;
  /* ring buffer */
  if (q->tail >= QUEUESIZE)
    q->tail = 0;
  /* queue overflow */
  if (q->tail == q->head)
    exit(1);
}

struct cost dequeue(struct queue *q) {
  struct cost c;
  /* queue underflow */
  if(q->head == q->tail) {
    c.x = c.y = c.c = -1;
    c.d = 'e';
  } else {
    c = q->pos[q->head];
    q->head += 1;
    /* ring buffer */
    if(q->head >= QUEUESIZE)
      q->head = 0;
  }
  return c;
}

int search(struct queue *q, struct cost c) {
  int i;
  for (i = q->head; i < q->tail; i ++)
    if (q->pos[i].x == c.x && q->pos[i].y == c.y) 
      return 1;
  return 0;
}
