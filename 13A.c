#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LISTMAX 1000

typedef char * elementtype;

typedef struct {
  elementtype music[LISTMAX];
  int n;
} ListPlayer;

ListPlayer LP_init();
ListPlayer LP_addmusic(ListPlayer lp, elementtype music);
void LP_play(ListPlayer lp, int b, int e);
void LP_search(ListPlayer lp, char *buf);
void chomp(char *buf, int n);

int main() {
  ListPlayer myplayer;
  char *music;
  int b, e, d, bi, ci;
  char buf[1024], cmdbuf[16], cmd;

  myplayer = LP_init();

  while(1) {
    fgets(buf, sizeof(buf), stdin);
    chomp(buf, sizeof(buf));
    if(buf[0] == '.')
      break;
    music = strdup(buf);
    myplayer = LP_addmusic(myplayer, music);
  }

  /* command parser */
  while(1){
    b = e = d = 0;
    fgets(buf, sizeof(buf), stdin);
    bi = 0;
    ci = 0;
    while(isdigit(buf[bi])) {
      cmdbuf[ci] = buf[bi];
      bi += 1;
      ci += 1;
    }
    cmdbuf[ci] = '\0';
    b = atol(cmdbuf);
    if(buf[bi] == ',') {
      bi += 1;
      ci = 0;
      while(isdigit(buf[bi])) {
        cmdbuf[ci] = buf[bi];
        bi += 1;
        ci += 1;
      }
      cmdbuf[ci] = '\0';
      e = atol(cmdbuf);
    }
    cmd = buf[bi];
    if(cmd != '/'){
      bi += 1;
      ci = 0;
      while (isdigit(buf[bi])) {
        cmdbuf[ci] = buf[bi];
        bi += 1;
        ci += 1;
      }
      cmdbuf[ci] = '\0';
      d = atol(cmdbuf);
    }
    /* command execution */
    if (cmd == 'p') {
      LP_play(myplayer, b, e);
    } else if (cmd == '/') {
      chomp(&buf[bi + 1], sizeof(buf) - bi - 1);
      LP_search(myplayer, &buf[bi + 1]);
    } else if (cmd == '.') {
      break;
    }
  }

  return 0;
}

void LP_search(ListPlayer lp, char *buf) {
  printf("LP_search : %s size %d\n", buf, (int)strlen(buf));
  /*
  Question B
  */

}

ListPlayer LP_addmusic(ListPlayer lp, elementtype music) {
  int j;

  if(lp.n >= LISTMAX)
    return lp;
  
  j = 1;
  while(j <= lp.n) {
    if(strcmp(lp.music[j], music) > 0) {
      elementtype tmp;
      tmp = lp.music[j];
      lp.music[j] = music;
      music = tmp;
    }
    j += 1;
  }
  
  lp.music[j] = music;
  lp.n += 1;
  /**/
//  for(j = 0; j < lp.n; j += 1)
//  printf("music[%d] : %s\n", j, lp.music[j]);
  /**/

  return lp;
}

void LP_play(ListPlayer lp, int b, int e) {
  if(e < b)
    e = b;
  int i = b;

  while(i <= e) {
    printf("%s\n", lp.music[i]);
    i += 1;
  }
}

ListPlayer LP_init() {
  ListPlayer lp;
  lp.n = 0/*LISTMAX - 1*/;
  lp.music[0] = strdup(""); /* 番兵 */
  return lp;
}

void chomp(char *buf, int n)  {
  int i;
  for(i = 0; i < n; i += 1) {
    if(buf[i] == '\n') {
      buf[i] = '\0';
      break;
    }
  }
}
