/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

/* REMOVE this entire comment, and ADD your definition of the type List
 * here, along with any other definitions you need for it.
 *
 * (You can add your name to the copyright notice above if you like, since
 * you will have written part of the code in this file).
 *
 * NOTE: if you write helper functions in your list.c you should NOT add
 * their prototypes to this header file.  In this case your helper functions
 * will be defined and called only from the file list.c, so their prototypes
 * should just be put at the top of that file- and your helper functions
 * should also be made static.
 */

void init(List *const list);
int append(List *const list, int new_value);
int prepend(List *const list, int new_value);
int size(List *const list);
int find(List *const list, int value);
int delete(List *const list, unsigned int position);
void print(List *const list);
