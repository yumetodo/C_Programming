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
ListPlayer LP_addmusic_insertion(ListPlayer lp, elementtype music);
ListPlayer LP_merge_sort(ListPlayer lp, int l, int r);
void LP_play(ListPlayer lp, int b, int e);
void LP_search(ListPlayer lp, char *buf);
void chomp(char *buf, int n);

int main() {
  ListPlayer myplayer;
  char *music;
  int b, e, d, bi, ci, /* merge sort */i = 0;
  char buf[1024], cmdbuf[16], cmd;

  myplayer = LP_init();

  while(1) {
    fgets(buf, sizeof(buf), stdin);
    chomp(buf, sizeof(buf));
    if(buf[0] == '.')
      break;
    music = strdup(buf);
    myplayer = LP_addmusic_insertion(myplayer, music);
  }
  i = myplayer.n + 1;
  while(1) {
    fgets(buf, sizeof(buf), stdin);
    chomp(buf, sizeof(buf));
    if(buf[0] == '.')
      break;
    music = strdup(buf);
    myplayer.music[i] = music;
    i += 1;
    myplayer.n += 1;
  }
  /* merge sort */
  myplayer = LP_merge_sort(myplayer,1, myplayer.n);
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
//  printf("LP_search : %s\nsize: %d\n", buf, (int)strlen(buf));
  int i, j, len;
  char *top;
  i = 0;
  top = buf;
 
  while(i <= lp.n) {
    j = 0;
    while(lp.music[i][j] != '\0') {
      if(lp.music[i][j] == *buf) {
        j += 1;
        buf += 1;
        if(*buf == '\0') {
          printf("%s\n", lp.music[i]);
          ;
        }
      }
      else {
        buf = top;
        break;
      }
    }
    i += 1;
  }
}
  
ListPlayer LP_addmusic_insertion(ListPlayer lp, elementtype music) {
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

  return lp;
}

ListPlayer LP_merge_sort(ListPlayer lp, int l, int r) {
  int i, j, k, m;
  ListPlayer mp, np;
  mp = np = LP_init();
  
  if(l < r) {
    m = (l + r) / 2;
    LP_merge_sort(lp, l, m);
    LP_merge_sort(lp, m + 1, r);
    for(i = m; i >= l; i -= 1)
      mp.music[i] = lp.music[i];
    i = l;
    for(j = m + 1; j <= r; j += 1)
      mp.music[r + m + 1 - j] = lp.music[j];
    j = r;
    for(k = l; k <= r; k += 1) {
      if(strcmp(mp.music[i], mp.music[j]) < 0)
        np.music[k] = mp.music[i ++];
      else
        np.music[k] = mp.music[j --];
    }
  }
  np.n = k - 1;
//  for(i = 1; i <= lp.n; i += 1)
//    printf("player[%d]: %s\n", i, lp.music[i]);
//  printf("\n");
  return np;
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

