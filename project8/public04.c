#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 4 (public04.c)
 *
 * Tests using mkdir() and touch() to create a filesystem with mixed files
 * and subdirectories, and lists them using ls().
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
  mkdir(&filesystem, "numbat");
  mkdir(&filesystem, "quokka");
  touch(&filesystem, "strawberry");
  touch(&filesystem, "raspberry");
  mkdir(&filesystem, "koala");

  ls(&filesystem, ".");

  return 0;
}
