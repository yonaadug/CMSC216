#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 9 (public09.c)
 *
 * Tests some special cases for the touch() and mkdir() functions.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  /* these special characters are valid */
  mkdir(&filesystem, "chippy-chipmunk");
  mkdir(&filesystem, "squiggley$squirrel");
  touch(&filesystem, "portia*porcupine");
  ls(&filesystem, ".");
  printf("\n");

  /* but '/' cannot appear anywhere in a file or directory name (error case) */
  mkdir(&filesystem, "chippy/chipmunk");
  mkdir(&filesystem, "/squiggleysquirrel");
  mkdir(&filesystem, "portiaporcupine/");
  ls(&filesystem, ".");
  printf("\n");

  /* these are also either error cases or just have no effect */
  touch(&filesystem, ".");
  mkdir(&filesystem, "/");
  touch(&filesystem, "..");
  ls(&filesystem, ".");
  
  return 0;
}
