#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 1 (public01.c)
 *
 * Tests calling print_instruction() with arithmetic and logical
 * instructions.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  printf("%d",is_valid_instruction(0x70190));
  
  return 0;
}
