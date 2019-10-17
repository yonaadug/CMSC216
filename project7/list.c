/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 *
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void init(List *const list) {
    if (list != NULL) {
        *list = malloc(sizeof(Node));
        (*list)->head = (*list);     
    }
}


int append(List *const list, int new_value) {
    
    Node * temp;
    Node * node;

    if (list != NULL) {

        node = malloc(sizeof(Node));

        if (node != NULL) {
            temp = (* list)->head;
            node->head = (* list)->head;
            node->data = new_value;


            while (1) {
                if (temp->next == NULL) {
                    temp->next = node;
                    node->prev = temp;

                    return 1;
                } else {
                    temp = temp->next;
                }
            }

        }
    }

    return 0;
}

int prepend(List *const list, int new_value) {

    Node *head;
    Node *next_node;
    Node *node;

    if (list != NULL) {

        head = (*list)->head;
        next_node = head->next;
        node = malloc(sizeof(Node));

        if(node != NULL) {

            node->head = head;
            node->data = new_value;

            head->next = node;
            node->prev = head;
            node->next = next_node;

            return 1;
        }
    }

    return 0;
}

int size(List *const list) {
    Node *temp = (*list)->head;
    int size = 0;
    
    if (list != NULL) {
        while(temp->next != NULL) {
            size += 1;
            temp = temp->next;
        }
    }   

    return size;
}

int find(List *const list, int value) {

    Node *temp = ((*list)->head)->next;
    int index = 0;

    if (list != NULL) {
        while (temp != NULL && temp->data != value) {
            index += 1;
            temp = temp->next;
            
        }

        if (temp == NULL || temp->data != value)
            return -1;
        else
            return index;
    }

    return -1;
}

int delete(List *const list, unsigned int position) {

    Node *temp, *prev_node, *next_node;
    int index;

    if (list != NULL && position >= 0) {
        temp = (*list)->head;
        index = -1;


        while (temp != NULL && position != index) {
            index += 1;
            temp = temp->next;
        }

        if (temp != NULL && position == index) {
            prev_node = temp->prev;
            next_node = temp->next;

            free(temp);
            prev_node->next = next_node;

            if (next_node != NULL) {
                next_node->prev = prev_node;
            }

            return 1;
        }
    }

    return 0;
}

void print(List *const list) {

    Node *temp;
    if(list != NULL && (*list)->head != NULL) {
        temp = ((*list)->head)->next;

        while (temp != NULL) {
            printf("%d",temp->data);
            temp = temp->next;

            if (temp != NULL) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }

    return;
}
