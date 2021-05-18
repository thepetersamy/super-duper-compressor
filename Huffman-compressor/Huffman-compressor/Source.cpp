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
	//FILE* file1 = fopen(filePath, "w");
	//fclose(file1);

	FILE *file = fopen(filePath, "a");
	for (int ch = 0; ch < sizeOfCodesMap; ch++)
	{
		if (codesMap[ch])
		{
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

size_t getFileCharNumbers(FILE* file)
{  
    size_t count = 0;  
	fseek(file, 0, SEEK_SET);
    char c;  
    for (c = getc(file); c != EOF; c = getc(file))
        count = count + 1;

    fclose(file);
  
    return count;
} 

int binaryWritingFile(char srcName[], char dstName[], char *codesMap[])
{
	char x = 127;
	FILE *src, *dst;
	src = fopen(srcName, "r");
	if (!src)
	{
		printf("Cannot read input file");
		return -2;
	}
	dst = fopen(dstName, "wb+");
	if (!dst)
	{
		printf("Cannot create output file");
		return -2;
	}
	char currentChar;
	// fprintf(dst, "%c%c", x, 3);
	// int count = 0;
	// char _8bin[] = "";
	while ((currentChar = fgetc(src)) != EOF)
	{
		fprintf(dst, "%s", codesMap[currentChar]);
	}
	int charNumb;
	charNumb = ftell(dst); 
	
	fseek(dst, 0, SEEK_SET); //to start from the begining
	
	int extraZeros;

	extraZeros = charNumb % 8;
	for(int i = 0; i < extraZeros; i++)
		fprintf(dst,"0");
	
	// while ((currentChar = fgetc(dst)) != EOF)
	// {
	// 	// int digit = (int)currentChar;
	// 	count++;
	// 	_8bin[count] = currentChar;
	// 	if (count == 8)
	// 	{
	// 		printf("%d", count);
	// 	}
	// 	// fwrite();
	// }
	fclose(src);
	fclose(dst);
}
int main()
{
	int x = 1227;
	printf("%8d", x);
	Node *LinkedTree = NULL;

	int frequencyMap[256];
	char *codesMap[256];
	char *codesMapNew[256];
	initCodesMap(codesMapNew);
	char current[50];
	current[0] = '\0';

	char path[] = "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\Huffman-compressor\\Huffman-compressor\\test.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

	LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);

	// copyCodesMapToTable(&allCodesTable, codesMap);
	// HashTable tabel[getSizeOfCodesMap(codesMap)];

	int codesMapSize = getSizeOfCodesMap(codesMap);

	serializeCodesMap(codesMap, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");

	binaryWritingFile(path, "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\Huffman-compressor\\Huffman-compressor\\out.com", codesMap);
	printCodes(codesMap);
	//deSerializeCodesMap(codesMapNew, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	//serializeCodesMap(codesMapNew, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");

	return 0;
}