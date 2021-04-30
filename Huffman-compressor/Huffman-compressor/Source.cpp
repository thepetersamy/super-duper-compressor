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


bool isLeaf(Node* root) {
	return root->left == NULL && root->right == NULL;
}

void generateCodes(Node* root, char currentCode[], char* map[]) {
	if (!root)
		return;
	
	if (isLeaf(root)) {
		map[root->data] = currentCode;
	}

	if (isLeaf(root)) {
		generateCodes(root->left, strcat(currentCode, "0"), map);
		generateCodes(root->right, strcat(currentCode, "1"), map);
	}
}


int main() {

	Node* ll=NULL;
	int map[256];
	generateFrequencyTable("C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\Huffman-compressor\\Huffman-compressor\\test.txt", map);

	ll = generatePriorityQueue(ll, map);
	//printList(ll);
    printFrequencyTable(map);
	ll = buildHuffmanTree(ll);

    ll = buildHuffmanTree(ll);



    return 0;
}
