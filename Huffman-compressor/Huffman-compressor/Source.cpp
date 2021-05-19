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
	FILE *file1 = fopen(filePath, "w");
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

size_t getFileCharNumbers(FILE *file)
{
	size_t count = 0;
	fseek(file, 0, SEEK_SET);
	char c;
	for (c = getc(file); c != EOF; c = getc(file))
		count = count + 1;

	fclose(file);

	return count;
}

// int pow2(int x, int n) {
// 	float result = 1;
// 	for (int i = 0; i < n; i++) {
// 		result = result * x;
// 	}
// 	return result;
// }
int convertBinToDec(int n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}
int convertStrToInt(char str[]){
	int result = 0;
	for(int i = 0; i < 8; i++){
		result = result * 10 + ( str[i] - '0' );
	}
	return result;
}
int binaryWritingFile(char srcName[], char dstName[], char *codesMap[])
{
	char x = 127;
	FILE *src, *tmpFile, *dst;
	src = fopen(srcName, "r");
	if (!src)
	{
		printf("Cannot read input file");
		return -2;
	}

	tmpFile = fopen("tmp.bin", "wb+");
	if (!tmpFile)
	{
		printf("Cannot create output file");
		return -2;
	}
	dst = fopen(dstName, "wb+");
	if (!dst)
	{
		printf("Cannot create output file");
		return -2;
	}
	char currentChar;
	// fprintf(tmpFile, "%c%c", x, 3);
	// int count = 0;
	// char _8bin[] = "";

	while ((currentChar = fgetc(src)) != EOF) //convertBinToDec from codesMap[] to 0/1
	{
		fprintf(tmpFile, "%s", codesMap[currentChar]);
	}

	int totalFileBits;
	totalFileBits = ftell(tmpFile); //total numbers in file

	fseek(tmpFile, 0, SEEK_SET); //to start from the begining

	int extraZeros;
	extraZeros = 8 - (totalFileBits % 8);
	for (int i = 0; i < extraZeros; i++)
		fprintf(tmpFile, "0");

	fseek(src, 0, SEEK_SET);
	while ((currentChar = fgetc(src)) != EOF) //reconvert src from codesMap[] after current zeros
	{
		fprintf(tmpFile, "%s\n", codesMap[currentChar]);
	}

	fseek(tmpFile, 0, SEEK_SET);

	int eightNums = ftell(tmpFile) / 8;
	int counter = 0;
	char currentCode[8];
	while ((currentChar = fgetc(tmpFile)) != EOF){
		char currentCharStr[2];
		currentCharStr[0] = currentChar;
		currentCharStr[1] = '\0';
		strcat(currentCode, currentCharStr);
		// printf("%s", currentCharStr);
		
		if (++counter % 8 == 0){ //BYT3AML M3AHOM B3D MB2O 8 ASLUN
			printf("code : %s\n", currentCode);
			int decEq = convertBinToDec(convertStrToInt(currentCode));
			fprintf(dst, "%d ", currentCode);
			currentCode[0] = '\0';
		}
	}

	// int *eightBin = (int *)malloc(sizeof(int));
	// int count;
	// while ((currentChar = fgetc(tmpFile)) != EOF)
	// {
	// 	// int digit = (int)currentChar;
	// 	count++;
	// 	eightBin[count] = currentChar;
	// 	if (count == 8)
	// 	{
	// 		printf("%d", count);
	// 	}
	// 	// fwrite();
	// }
	fclose(src);
	fclose(tmpFile);
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
	printf("%d\n", codesMapSize);
	serializeCodesMap(codesMap, codesMapSize, "TestingFiles/codesbin.cod");

	binaryWritingFile(path, "C:\\Users\\Mohamed-Essam\\Desktop\\huffman-compressor\\Huffman-compressor\\Huffman-compressor\\out.com", codesMap);
	// printCodes(codesMap);
	// deSerializeCodesMap(codesMapNew, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");
	//serializeCodesMap(codesMapNew, codesMapSize, "D:/stuff/huffman-compressor/testingFiles/codesbin.cod");

	return 0;
}