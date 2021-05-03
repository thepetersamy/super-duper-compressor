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

void insertItemTable(HashTable *table, char character, char code[]){
	// table = (HashTable*)malloc(sizeof(HashTable));
	table->character = character;
	// table->code = code;
	stpcpy(table->code, code);

}
void printTable(HashTable tables[], int sizeOfTable){
	for(int i = 0; i < sizeOfTable; i++){
		printf("%c : %s\n", tables[i].character, tables[i].code);
	}
}

struct HashTable* deleteItemTable(HashTable* table){}

void copyCodesMapToTable(HashTable hashTables[], char* codesMap[]){
	
	int counter = 0;
	for(int ch = 0; ch < 256; ch++){
		if(codesMap[ch]){
			insertItemTable(&hashTables[counter++], ch, codesMap[ch]);
		}
	}

}
void serializeHashTable(HashTable table[],int sizeOfTable, const char* filePath){

	FILE *file = fopen(filePath, "wb");
	// for(int i = 0; i < sizeOfTable; i++){
		fwrite(table, sizeof(HashTable), sizeOfTable, file);
	// }
	fclose(file);

}
// not woring yet
void deserializeHashTable(HashTable table[],int sizeOfTable, char* filePath){
	FILE *file = fopen(filePath, "r");
	fread(table, sizeof(HashTable), 1, file);
}
int main() {

	Node* LinkedTree = NULL;

	int frequencyMap[256];
	char* codesMap[256];
	char current[50];
	current[0] = '\0';
	
	char* path = "/home/peter/stuff/huffman-compressor/testingFiles/3.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

    LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);

	
	
	// copyCodesMapToTable(&allCodesTable, codesMap);

	// HashTable tabel[getSizeOfCodesMap(codesMap)];
	int hashTableSize = getSizeOfCodesMap(codesMap);
	HashTable *allCodesTable = (HashTable*)malloc(sizeof(HashTable)*hashTableSize);
	HashTable *allCodesTableNew = (HashTable*)malloc(sizeof(HashTable)*hashTableSize);
	
	HashTable table;
	// HashTable allTables[23];
	// insertItemTable(&table, 'a', "0101");
	// insertItemTable(&table, 'b', "0101");
	copyCodesMapToTable(allCodesTable, codesMap);
	// printTable(allCodesTable, hashTableSize);
	serializeHashTable(allCodesTable, hashTableSize, "/home/peter/stuff/huffman-compressor/testingFiles/codes.cod");

	deserializeHashTable(allCodesTableNew, hashTableSize, "/home/peter/stuff/huffman-compressor/testingFiles/codes.cod");
	// printTable(allCodesTableNew, hashTableSize);

    return 0;
}