#include <stdio.h>


typedef enum { PLUS, DIFF, MULT, QUOT, MOD, AND, OR, NOT, BR, READ, WRT, MOVE,
	       LW, SW, LI } Operation;


int main()
{
  enum d;
  enum t;
  d = DIFF;
  t = DIFF;
  if(d == t )
    printf("%d",d);


  return 0;
}
