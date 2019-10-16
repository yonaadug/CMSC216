#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  int data;
} Node;

/* create a list with three nodes with values 10, 20, and 30 */
void create_test_list(Node **head) {
  *head= malloc(sizeof(Node));
  if (*head == NULL)
    exit(-1);
  (*head)->data= 10;

  (*head)->next= malloc(sizeof(Node));
  if ((*head)->next == NULL)
    exit(-1);
  (*head)->next->data= 20;

  (*head)->next->next= malloc(sizeof(Node));
  if ((*head)->next->next == NULL)
    exit(-1);
  (*head)->next->next->data= 30;
}

int main(void) {
  Node *root, *current;

  /* create a small list */
  create_test_list(&root);

  /* now remove the first node */
  current= root;
  root= root->next;

  /* and add the old first node to the end of the list */
  root->next->next= current;

  /* now print the values in the list's nodes */
  current= root;
  while (current != NULL) {
    printf("%d ", current->data);
    current= current->next;
  }
  printf("\n");

  return 0;
}
