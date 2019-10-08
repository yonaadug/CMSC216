#include <stdio.h>

int main() {
  int a, b, c, x, y, z;

  a = 4;
  b = 3;
  c = 10;

  printf("a: %d, b: %d, c: %d", a,b,c);
  
  z = (a++, a+b);

  printf("\na: %d, b: %d, c: %d, z: %d", a,b,c,z);
  
  y = ((a = a +b), a + b);

  printf("\na: %d, b: %d, c: %d, y: %d", a,b,c,y);

  x = y + z;

  printf("\na: %d, b: %d, c: %d, x: %d", a,b,c,x);

  return 0;
}
