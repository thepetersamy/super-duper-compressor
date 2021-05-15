#include "Utils.h"

int getSizeOfCodesMap(char *codesMap[])
{
	int counter = 0;
	for (int i = 0; i < 256; i++)
	{
		if (codesMap[i])
		{
			counter++;
		}
	}
	return counter;
}

void serializeCodesMap(char *codesMap[], int sizeOfCodesMap, const char *filePath)
{
	//clearing content "should be opt in future"
	FILE* file1 = fopen(filePath, "w");
	fclose(file1);

	// printf("%d\n", sizeOfCodesMap);
	FILE *file = fopen(filePath, "a");
	for (int ch = 0; ch < 256; ch++)
	{
		if (codesMap[ch] != NULL)
		{
			printf("%c%s\n", ch, codesMap[ch]);
			// fwrite(codesMap[i], sizeof(codesMap[i]), sizeOfCodesMap, file);
			fprintf(file, "%c%s\n", ch, codesMap[ch]);
			//printf("%c %s\n", ch, codesMap[ch]);
		}
	}
	fclose(file);
}
// shift all characters one place to the left starting with the given index
void shiftLeft(char str[])
{
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = str[i + 1];
	}
}
void deSerializeCodesMap(char *codesMap[256], const char *filePath)
{
	FILE *file = fopen(filePath, "r");

	/*while (!feof(file)) { 
		char c;
		char str[50];
		fscanf(file, "%c%s", &c, str);
	}*/
	char line[256];
	char code[30];
	initCodesMap(codesMap);
	while (fgets(line, 45, file))
	{
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

// int binaryWritingFile(char srcName[], char dstName[], char* codesMap[])
// {
// 	FILE *src, *dst;
// 	src = fopen(srcName, "r");
// 	if (!src)
// 	{
// 		printf("Cannot read input file");
// 		return -2;
// 	}
// 	dst = fopen(dstName, "wb");
// 	if (!dst)
// 	{
// 		printf("Cannot create output file");
// 		return -2;
// 	}

// 	char currentChar;
// 	while ((currentChar = fgetc(src)) != EOF)
// 	{
// 		// fprintf(dst, "%s", codesMap[currentChar]);
// 		fwrite(); 
// 	}

// 	fclose(src);
// 	fclose(dst);
// }
int main()
{

	Node *LinkedTree = NULL;

	int frequencyMap[256];
	char *codesMap[256];
	char *codesMapNew[256];
	initCodesMap(codesMapNew);
	char current[50];
	current[0] = '\0';

	char path[] = "TestingFiles/1.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

	LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);

	// copyCodesMapToTable(&allCodesTable, codesMap);
	// HashTable tabel[getSizeOfCodesMap(codesMap)];

	int codesMapSize = getSizeOfCodesMap(codesMap);
	printf("%d\n", codesMapSize);
	serializeCodesMap(codesMap, codesMapSize, "TestingFiles/codesbin.cod");

	// binaryWritingFile(path, "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\Huffman-compressor\\Huffman-compressor\\out.com", codesMap);
	// printCodes(codesMap);
	// deSerializeCodesMap(codesMapNew, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	//serializeCodesMap(codesMapNew, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");

	return 0;
}