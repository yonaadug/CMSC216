#include <stdio.h>

#define P 5

int main(){

  unsigned short i;
  int j;
  printf("%d\n", (int) sizeof(unsigned short));

  j = 65535+1;
  i = 65535;
  printf("%d\n", i);
  i=i+1;
  printf("%d\n", i);
  printf("%d\n", (int) sizeof(P));

  return 0;

}
