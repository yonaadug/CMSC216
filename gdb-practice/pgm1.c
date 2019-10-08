#include <stdio.h>

/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

static int power(int x, int y);

static int power(int x, int y) {
  if (x == y + 1)
    return x;
  else return x * power(x, y - 1);
}

int main(void) {
  int a, b, n;

  a= 2;
  b= 5;
  n= power(a, b);
  printf("%d to the %d is %d.\n", a, b, n);

  a= 5;
  b= 2;
  n= power(a, b);
  printf("%d to the %d is %d.\n", a, b, n);

  return 0;
}
