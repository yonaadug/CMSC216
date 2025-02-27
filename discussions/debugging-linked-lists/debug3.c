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
  (*head)->next->next->next= NULL;
}

void remove_first_element(Node **head) {
  if (*head != NULL) {
    *head= (*head)->next;
    free(head);
  }
}

int main(void) {
  Node *root, *current;

  /* create a small list */
  create_test_list(&root);

  /* now print the values in the list's nodes */
  current= root;
  while (current != NULL) {
    printf("%d ", current->data);
    current= current->next;
  }
  printf("\n");

  /* now destroy the list */
  while (root != NULL)
    remove_first_element(&root);

  /* now try printing the list again */
  current= root;
  while (current != NULL) {
    printf("%d ", current->data);
    current= current->next;
  }
  printf("\n");

  return 0;
}
