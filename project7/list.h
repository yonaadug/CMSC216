/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 *
 */

/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

typedef struct node {
	int data;  /* data*/
	struct node *next; /* pointer to next node */
      struct node *prev; /* pointer to previous node */
      struct node *head;
} Node;

typedef Node * List;

void init(List *const list);
int append(List *const list, int new_value);
int prepend(List *const list, int new_value);
int size(List *const list);
int find(List *const list, int value);
int delete(List *const list, unsigned int position);
void print(List *const list);
