/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 * 
 * This list.c file implements functions that can be used by 
 * the linked list struct.
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*Function intializes linked list*/
void init(List *const list) {
    if (list != NULL) {
        *list = malloc(sizeof(Node));

        if (*list == NULL)
            return;
        
        (*list)->head = (*list);
    }
}

/*Function that adds new node at the end of the linked list*/
int append(List *const list, int new_value) {
    
    Node *temp;
    Node *node;

    if (list != NULL) {

        node = malloc(sizeof(Node));

        if (node != NULL) {
            
            temp = *list;
            node->head = (*list)->head;
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

/*Function that adds the a new node in the beginning of linked list*/
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

/*Function that calculates the size of the linked list*/
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

/*Find that finds and element in the linked list
and returns the index of an element. But returns
-1 when the element is not in the list*/
int find(List *const list, int value) {

    /*Start at the first limit*/
    Node *temp = ((*list)->head)->next;
    /*Index to keep track of location in linked list*/
    int index = 0;

    if (list != NULL) {
        while (temp != NULL && temp->data != value) {
            index += 1;
            temp = temp->next;
            
        }

        /*Return index if value found or -1 if not found*/
        if (temp == NULL || temp->data != value)
            return -1;
        else
            return index;
    }

    return -1;
}

/*THis fuction deletes a node at a position in the list*/
int delete(List *const list, unsigned int position) {

    Node *temp, *prev_node, *next_node;
    int index;

    /*Check if list is not NULL and position is a valid
    number*/
    if (list != NULL && position >= 0) {
        temp = (*list)->head;
        index = -1;

        /*iterate through list and find element with index
        the same as position*/
        while (temp != NULL && position != index) {
            index += 1;
            temp = temp->next;
        }

        /*Delete element if temp is not null and connect list 
        together after freeing its memory*/
        if (temp != NULL && position == index) {
            prev_node = temp->prev;
            next_node = temp->next;

            /*Free the temp variable*/
            free(temp);
            prev_node->next = next_node;

            if (next_node != NULL) {
                next_node->prev = prev_node;
            }

            /*Successful deletion*/
            return 1;
        }
    }

    return 0;
}

/*This function prints the linked list elements*/
void print(List *const list) {

    Node *temp;

    /*Check if list is null and the head of list null*/
    if(list != NULL && (*list)->head != NULL) {

        /*Start at the first element*/
        temp = ((*list)->head)->next;

        /*Loop and print each element*/
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
