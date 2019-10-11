#include "row-sum.h"

/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

/* assumed row is valid */

int row_sum(int arr[][5], int row) {
  int i, sum= 0;

  for (i= 0; i < 5; i++)
    sum += arr[row][i];

  return sum;
}
