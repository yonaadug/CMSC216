#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 2 (public02.c)
 *
 * Tests the basic operation of the touch() function to create a filesystem
 * with several files, and lists them using the ls() function.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  touch(&filesystem, "chipmunk");
  touch(&filesystem, "platypus");
  touch(&filesystem, "numbat");
  touch(&filesystem, "quokka");
  touch(&filesystem, "koala");

  ls(&filesystem, ".");

  return 0;
}
