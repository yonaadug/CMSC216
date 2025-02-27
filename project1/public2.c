#include <stdio.h>
#include <assert.h>
#include "functions.h"

/* CMSC 216, Fall 2019, Project #1
 * Public test 2 (public2.c)
 *
 * Tests calling sum_of_cubes() with n = 1.
 *
 * (c) Larry Herman, 2018.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(sum_of_cubes(1) == 1);
  printf("\nTest passed!\n");

  return 0;
}
