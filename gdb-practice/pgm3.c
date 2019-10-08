#include <stdio.h>
#include <string.h>

/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

typedef struct {
  char name[50];
  short grade;
} Student;

static int find(Student students[], const char name_to_find[]);

static int find(Student students[], const char name_to_find[]) {
  int i, found;

  i= 0;
  while (strcmp(students[i].name, "") !=  0) {

    if (strcmp(students[i].name, name_to_find) == 0)
      found= i;
    else found= -1;

    i++;
  }

  return found;
}

int main(void) {
  Student roster[]= {
    {"Sally", 68},
    {"Fred", 71},
    {"Leslie", 87},
    {"Tracy", 83},
    {"Paul", 75},
    {"Rhonda", 97},
    {"Bob", 65},
    {"Sarah", 99},
    {"Joanne", 78},
    {"Stuart", 82},
    {"", 0}
  };
  int pos;

  /* first try looking up a student who should be found in the list */
  pos= find(roster, "Sarah");
  if (pos > 0)
    printf("Found student %s with grade %d at position %d in the roster.\n",
           "Sarah", roster[pos].grade, pos);
  else printf("Couldn't find student %s in the roster.\n", "Sarah");

  /* then try looking up a student who is not in the list */
  pos= find(roster, "Oswald");
  if (pos > 0)
    printf("Found student %s with grade %d at position %d in the roster.\n",
           "Oswald", roster[pos].grade, pos);
  else printf("Couldn't find student %s in the roster.\n", "Oswald");

  return 0;
}
