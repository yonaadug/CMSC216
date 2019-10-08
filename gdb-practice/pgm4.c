#include <stdio.h>

/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

#define COLS 6

static int sum_array_region(int arr[][COLS], int r1, int c1, int r2, int c2);

static int sum_array_region(int arr[][COLS], int r1, int c1, int r2, int c2) {
  int sum= 0;

  while (r1 <= r2)
    while (c1 <= c2) {
      sum += arr[r1][c1];
      r1++;
      c1++;
    }

  return sum;
}

int main(void) {
  int arr1[][COLS]= {{4,  1, 10, 10,  1,  4},
                     {3, 10,  8,  7,  5,  6},
                     {4,  4,  3, 10,  3,  7},
                     {3,  7,  3,  4,  2,  4},
                     {8, 10, 10,  2, 10,  6},
                     {3,  1, 10,  4, 10,  6},
                     {7,  7,  1,  3,  8,  9},
                     {9,  2,  6, 10,  8,  2}};
  int arr2[][COLS]= {{2, 10,  5,  4,  2,  2},
                     {8,  6,  8,  4,  10, 5},
                     {9,  3,  1,  2,  9,  3},
                     {5,  4, 10,  9,  8, 10},
                     {8, 10,  2,  9,  7,  7},
                     {9, 10,  5,  5,  3, 10},
                     {2,  1,  5,  8,  7, 10},
                     {3,  9,  1,  6,  6,  7},
                     {8,  5,  7,  8,  4,  5},
                     {2,  1,  3,  5, 10,  8}};
  int x1, y1, x2, y2;

  x1= 1;
  y1= 3;
  x2= 2;
  y2= 4;
  printf("Sum of region between arr1[%d][%d] and arr1[%d][%d] is %d.\n",
         x1, y1, x2, y2, sum_array_region(arr1, x1, y1, x2, y2));

  x1= 2;
  y1= 4;
  x2= 3;
  y2= 7;
  printf("Sum of region between arr2[%d][%d] and arr2[%d][%d] is %d.\n",
         x1, y1, x2, y2, sum_array_region(arr2, x1, y1, x2, y2));

  return 0;
}
