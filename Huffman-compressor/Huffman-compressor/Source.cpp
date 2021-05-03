#include "Utils.h"



typedef struct HashTable {
   	char character;
	char code[50];   
}HashTable;

int getSizeOfCodesMap(char* codesMap[]){
	int counter = 0;
	for(int i = 0; i < 256; i++){
		if(codesMap[i]){
			counter++;
		}
	}
	return counter;
}

struct HashTable* insertItemTable(HashTable* table, char character, char code[]){
	table = (HashTable*)malloc(sizeof(HashTable));
	table->character = character;
	// table->code = code;
	stpcpy(table->code, code);

	return table;
}

struct HashTable* deleteItemTable(HashTable* table){}

void copyCodesMapToTable(HashTable* hashTables[], char* codesMap[]){
	
	int counter = 0;
	for(int ch = 0; ch < 256; ch++){
		if(codesMap[ch]){
			insertItemTable(hashTables[counter++], ch, codesMap[ch]);
		}
	}

}


int main() {

	Node* LinkedTree = NULL;

	int frequencyMap[256];
	char* codesMap[256];
	char current[50];
	current[0] = '\0';
	
	char* path = "/home/peter/stuff/huffman-compressor/testingFiles/1.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

    LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);

	


	HashTable *allCodesTable = (HashTable*)malloc(sizeof(HashTable)*getSizeOfCodesMap(codesMap));

	
	copyCodesMapToTable(&allCodesTable, codesMap);

	


    return 0;
}