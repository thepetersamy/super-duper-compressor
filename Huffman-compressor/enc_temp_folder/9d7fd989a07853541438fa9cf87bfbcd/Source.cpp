#include "Utils.h"

int getSizeOfCodesMap(char* codesMap[]){
	int counter = 0;
	for(int i = 0; i < 256; i++){
		if(codesMap[i]){
			counter++;
		}
	}
	return counter;
}

void serializeCodesMap(char* codesMap[],int sizeOfCodesMap, const char* filePath){
	 //clearing content "should be opt in future"
	//FILE* file1 = fopen(filePath, "w");
	//fclose(file1);

	FILE *file = fopen(filePath, "a");
	for(int ch = 0; ch<sizeOfCodesMap; ch++){
		if(codesMap[ch]){
			// fwrite(codesMap[i], sizeof(codesMap[i]), sizeOfCodesMap, file);	
			fprintf(file, "%c%s\n", ch, codesMap[ch]);
			//printf("%c %s\n", ch, codesMap[ch]);
		}
	}
	fclose(file);
}
// shift all characters one place to the left starting with the given index
void shiftLeft(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = str[i + 1];
	}
}
void deSerializeCodesMap(char* codesMap[256], const char* filePath){
	FILE *file = fopen(filePath, "r");
	

	//char currentChar;
	//while ((currentChar = fgetc(file)) != EOF) {

	//	char c;
	//	char str[50];
	//	// str[0] = '\0';
	//	fscanf(file, "%c%s", &c, str);
	//	// printf("%c : %s\n", c, str);
	//	// codesMap[(int)c] = str;
	//	// strcpy(codesMap[c], str);
	//	printf("%s\n", str);
	//	// for(int i = 0; i<strlen(str); i++){
	//	// 	codesMap[c][i] = str
	//	// }

	//}
	/*while (!feof(file)) { 
		char c;
		char str[50];
		fscanf(file, "%c%s", &c, str);
	}*/
	char line[256];
	char code[30];
	initCodesMap(codesMap);
	while (fgets(line, 45, file)) {
		//concatenateString(code, line);
		char character = line[0];
		shiftLeft(line);
		printf("%c : %s\n", character, line);
		
		//strcpy(line, codesMap[character] );
		
		//codesMap[(int)character] = line;
	}
	//printf("\n");
	fclose(file);

}


int main() {

	Node* LinkedTree = NULL;

	int frequencyMap[256];
	char* codesMap[256];
	char* codesMapNew[256];
	initCodesMap(codesMapNew);
	char current[50];
	current[0] = '\0';
	
	char path[] = "D:\\stuff\\huffman-compressor\\testingFiles\\3.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

    LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);
	
	
	// copyCodesMapToTable(&allCodesTable, codesMap);
	// HashTable tabel[getSizeOfCodesMap(codesMap)];

	int codesMapSize = getSizeOfCodesMap(codesMap);

	serializeCodesMap(codesMap, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	printCodes(codesMap);
	//deSerializeCodesMap(codesMapNew, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	//serializeCodesMap(codesMapNew, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	

	

    return 0;
}