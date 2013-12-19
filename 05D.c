#include <stdio.h>

int pay(int x);

int main(void) {
  int y;

  scanf("%d", &y);
  printf("%d\n", pay(y));

  return 0;  
}

int pay(int x) {
  int count = 0;

  if(x - 1000 >= 0) {
    count += pay(x - 1000);
    if(x - 500 >= 0) {
      count += pay(x - 500);
      if(x - 100 >= 0) {
        count += pay(x - 100);
        if(x - 50 >= 0) {
          count += pay(x - 50);
          if(x - 10 >= 0) {
            count += 1;
          }
        }
      }
    }
  } else if(x - 500 >= 0){
    count += pay(x - 500);
    if(x - 100 >= 0) {
      count += pay(x - 100);
      if(x - 50 >= 0) {
        count += pay(x - 50);
        if(x - 10 >= 0) {
          count += 1;
        }
      }
    }
  } else if(x - 100 >= 0) {
    count += pay(x - 100);
    if(x - 50 >= 0) {
      count += pay(x - 50);
      if(x - 10 >= 0) {
        count += 1;
      }
    }
  } else if(x - 50 >= 0) {
    count += pay(x - 50);
    if(x - 10 >= 0) {
      count += 1;
    }
  } else {
    return 1;
  }

  return count;
}
