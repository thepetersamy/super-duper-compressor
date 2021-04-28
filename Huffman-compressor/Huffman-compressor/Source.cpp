#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

int main(){

    int x;
    char y;
    Node* head=NULL;
    
    head=insertSort(head,80,'a');
    head=insertSort(head,50,'a');
    head=insertSort(head,60,'a');
    head=insertSort(head,70,'a');
    head=findRoot(head);

    return 0;
}
