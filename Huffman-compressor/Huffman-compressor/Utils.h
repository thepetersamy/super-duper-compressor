#ifndef HUFFMAN_UTILS_H
#define HUFFMAN_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "FrequencyTable.h"
#include "LinkedList.h"
// #include "HashTable.h"

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

char *concatenateString(char* str1, const char* str2){
	int str1Len = strlen(str1);
	int str2Len = strlen(str2);
	int strLen = str1Len + str2Len + 1 ;
	
	char *result = (char *)malloc(sizeof(char)*strLen);
	
	int i;
	for(i = 0; i < str1Len; i++)
		result[i] = str1[i];
	
	for(int j=0;j<str2Len; j++, i++)
		result[i] = str2[j];
	
	result[i] = '\0';


	return result;
	

}

char* strcat2(char* str1, const char* str2) {
	// the default strcat was causing some problems that i did't feel like looking into so i made my own
	// (it's WET code i know but i don't do that much often)
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int len3 = len1 + len2 + 1;

	char* str = (char*)malloc(sizeof(char) * len3);
	str[0] = '\0';
	int i;

	for (i = 0; i < len1; i++) {
		str[i] = str1[i];
	}
	for (int j = 0; j < len2; j++, ++i) {
		str[i] = str2[j];
	}
	str[i] = '\0';

	return str;
}


void initCodesMap(char* codesMap[]){

	for(int i=0; i<256; i++){
		codesMap[i] = NULL;
	}
}

void encodeTree(Node* root, char currentCode[], char* codesMap[]) {
	if (!root)
		return;

	else if (isLeaf(root)) {
		codesMap[root->data] = currentCode;
	}
	encodeTree(root->left, concatenateString(currentCode, "0"), codesMap);
	encodeTree(root->right, concatenateString(currentCode, "1"), codesMap);
}

void printCodes(char* codesMap[]){
	for(int i = 0; i < 256; i++){
		if(codesMap[i]){
			printf("%c : %s\n",i, codesMap[i]);
		}
	}
}

void generateCodes(Node* root, char* currentCode, char* codesMap[]){
	initCodesMap(codesMap);	
	encodeTree(root, currentCode, codesMap);
	//printCodes(codesMap);
}

#endif //HUFFMAN_UTILS_H