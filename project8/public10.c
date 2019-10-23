#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #8
 * Public test 10 (public10.c)
 *
 * Tests creating a larger filesystem with various files and directories,
 * and calls all of the functions on it.
 *
 * Link this example with the driver object file driver.o, and run the
 * executable with input redirected from public10.input.  (Hint: you used
 * input redirection to run every test in Project #2.)  (Hint #2: Makefile
 * rules for this test will be different than for the other ones.)
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  driver(&filesystem);

  return 0;
}
