#ifndef HUFFMAN_HASHTABLE_H
#define HUFFMAN_HASHTABLE_H

typedef struct HashTable {
   	char character;
	char code[50];   
}HashTable;

void insertItemTable(HashTable *table, char character, char code[]){
	// table = (HashTable*)malloc(sizeof(HashTable));
	table->character = character;
	// table->code = code;
	strcpy(table->code, code);

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
	printf("file size: %d\n",sizeof(file));

	fclose(file);

}

void serializeHashTable2(HashTable table[],int sizeOfTable, const char* filePath){

	FILE *file = fopen(filePath, "a");
	for(int i = 0; i<sizeOfTable; i++){
		fprintf(file, "%c%s\n", table[i].character, table[i].code);
	}
	printf("file size: %d\n",sizeof(file));

	fclose(file);

}
// not woring yet
void deserializeHashTable(HashTable table[],int sizeOfTable, char* filePath){
	FILE *file = fopen(filePath, "r");
	fread(table, sizeof(HashTable), 1, file);
}








#endif //HUFFMAN_HASHTABLE_H