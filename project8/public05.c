#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 5 (public05.c)
 *
 * Tests using the cd() function to change to a subdirectory, creates some
 * files in it, and lists them.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "chipmunk");
  cd(&filesystem, "chipmunk");

  mkdir(&filesystem, "koala");
  mkdir(&filesystem, "platypus");
  mkdir(&filesystem, "numbat");
  mkdir(&filesystem, "quokka");

  /* this will not list chipmunk, because we are inside chipmunk */
  ls(&filesystem, ".");

  return 0;
}
