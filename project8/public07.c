#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 7 (public07.c)
 *
 * Tests some special cases for the ls() function.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "chipmunk");
  touch(&filesystem, "pear");
  mkdir(&filesystem, "platypus");
  touch(&filesystem, "papaya");
  touch(&filesystem, "orange");

  cd(&filesystem, "chipmunk");

  mkdir(&filesystem, "koala");
  mkdir(&filesystem, "numbat");
  mkdir(&filesystem, "quokka");
  touch(&filesystem, "strawberry");
  touch(&filesystem, "raspberry");

  ls(&filesystem, ".");
  printf("\n");

  ls(&filesystem, "..");
  printf("\n");

  ls(&filesystem, "/");

  return 0;
}
