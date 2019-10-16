#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 8 (public08.c)
 *
 * Tests deleting a different element of a list.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  append(&list, 250);
  append(&list, 132);
  append(&list, 216);
  append(&list, 131);
  append(&list, 141);
  append(&list, 330);
  append(&list, 350);
  append(&list, 412);
  append(&list, 351);

  assert(size(&list) == 9);

  delete(&list, 7);

  assert(find(&list, 412) == -1);
  assert(size(&list) == 8);

  printf("All assertions experienced a favorable outcome!\n");

  return 0;
}
