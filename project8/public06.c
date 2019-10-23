#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 6 (public06.c)
 *
 * Tests using the cd() function to change to a subdirectory, and calls
 * pwd() from it.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "chipmunk");
  cd(&filesystem, "chipmunk");

  pwd(&filesystem);

  return 0;
}
