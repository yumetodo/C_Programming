#include <stdio.h>
#include <math.h>
#define EPSILON /* 縺薙％繧貞ョ夂セゥ */

double overlap(double x1, double y1, double x2, double y2);

int main(void) {
  printf("%f¥n", overlap(0.0, 0.0, 1.0, 1.0));
  return 0;
}

double overlap(double x1, double y1, double x2, double y2) {
  if(sqrt(x2 * x2 + y2 * y2) < 1)
    return ((x2 - x1) * (y2 - y1));
  else if(sqrt(x1 * x1 + y1 * y1) > 1)
    return 0;
  else
    return overlap(x1 / 2, ;
}
