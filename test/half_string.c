#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;


int main()
{
    char str1[] = "cattle";
    /*strncpy(str1, str1, i);*/
    str1[0] = 'd';
    printf("%s, %c", str1, str1[0]);
    return 0;
}
