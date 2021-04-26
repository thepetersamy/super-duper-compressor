#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

int main(){

    int x;
    char y;
    Node* head=NULL;
    head = insertLast(head, 1, 'a');
    head = removeFirst(head, &x, &y);


    return 0;
}
