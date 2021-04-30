#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FrequencyTable.h"
#include "LinkedList.h"
//#include "Utils.h"


Node *generatePriorityQueue(Node *h, int map[256]){
	for(int i=0; i<256; i++){
		if(map[i] != 0){
			h = insertSort(h, map[i], i);
		}
	}
	return h;
}



int main() {

	Node* ll=NULL;
	int map[256];
	generateFrequencyTable("/home/peter/stuff/huff3/test.txt", map);

	ll = generatePriorityQueue(ll, map);
	printList(ll);

	ll = buildHuffmanTree(ll);




    return 0;
}
