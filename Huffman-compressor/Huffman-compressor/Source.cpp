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
			// printf("%c%s\n", ch, codesMap[ch]);
			// fwrite(codesMap[i], sizeof(codesMap[i]), sizeOfCodesMap, file);
			fprintf(file, "%c%s\n", ch, codesMap[ch]);
			//printf("%c %s\n", ch, codesMap[ch]);
		}
	}
	fclose(file);
}

void serializeCodesMap2(std::map<char, std::string> &codesMap, const char *filePath)
{
	//clearing content "should be opt in future"
	FILE *file1 = fopen(filePath, "w");
	fclose(file1);

	// printf("%d\n", sizeOfCodesMap);
	FILE *file = fopen(filePath, "a");
	std::map<char, std::string>::iterator it;
	for(it = codesMap.begin(); it != codesMap.end(); it++){
		// printf("%c : %s\n", it->first, it->second);
		// std::cout<<it->first<<it->second<<std::endl;

		// printf("%c", it->first);
		fprintf(file, "%c", it->first);

		for(int i=0; it->second[i] != '\0'; i++){
			// printf("%c", it->second[i]);
			fprintf(file, "%c", it->second[i]);
		}
		fprintf(file, "\n");

		// fwrite(codesMap[i], sizeof(codesMap[i]), sizeOfCodesMap, file);
		// fprintf(file, "%c%s\n", ch, codesMap[ch]);
		//printf("%c %s\n", ch, codesMap[ch]);
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
		// printf("%c : %s\n", character, line);

		//strcpy(line, codesMap[character] );

		//codesMap[(int)character] = line;
	}
	//printf("\n");
	fclose(file);
}

void deserializeCodesMap2(std::map<char, std::string> &codesMap, const char*filePath){
	FILE *file = fopen(filePath, "r");
	char line[256];
	char code[30];
	
	while (fgets(line, 45, file)){

		char character = line[0];
		shiftLeft(line);
		std::string cppStr = line;
		codesMap.insert(std::pair<char,std::string>(character, cppStr));
		
		// printf("%c : %s\n", character, line);

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
void strcat3(char dst[], char src){
	int len = strlen(dst);	
	// printf("len : %d", len);
	dst[len] = src;
	dst[len+1] = '\0';
}
int compress(char srcName[], char dstName[], char *codesMap[]) {

	FILE *src, *tmpFile, *dst;
	src = fopen(srcName, "r");
	if (!src) {
		printf("Cannot read input file");
		return -2;
	}

	tmpFile = fopen("TestingFiles/tmp.bin", "wb+");
	if (!tmpFile) {
		printf("Cannot create output file");
		return -2;
	}
	dst = fopen(dstName, "wb+");
	if (!dst) {
		printf("Cannot create output file");
		return -2;
	}
	char currentChar;

	//convertBinToDec from codesMap[] to 0/1
	while ((currentChar = fgetc(src)) != EOF) {
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

	//reconvert src from codesMap[] after current zeros
	while ((currentChar = fgetc(src)) != EOF) {
		fprintf(tmpFile, "%s", codesMap[currentChar]);
	}

	fseek(tmpFile, 0, SEEK_SET);

	int eightNums = ftell(tmpFile) / 8;
	int counter = 0;
	char currentCode[8];
	currentCode[0] = '\0';
	while ((currentChar = fgetc(tmpFile)) != EOF){
		// char currentCharStr[2];
		// currentCharStr[0] = currentChar;
		// currentCharStr[1] = '\0';
		// strcat(currentCode, currentCharStr);
		// printf("%s", currentCharStr);
		// printf("code : %s\n", currentCode);
		// printf("%c", currentChar);
		strcat3(currentCode, currentChar);



		if (++counter % 8 == 0){ //BYT3AML M3AHOM B3D MB2O 8 ASLUN

			// printf("%s\n", currentCode);
			int decEq = convertBinToDec(convertStrToInt(currentCode));
			// printf("dec : %d\n", decEq);
			fprintf(dst, "%c", decEq);
			currentCode[0] = '\0';
		}
	}
	remove("tmp.bin");

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

void decompress(char srcName[], char dstName[], char *codesMap[]){

}
int main()
{Node *LinkedTree = NULL;

	int frequencyMap[256];
	char *codesMapOld[256];
	// char *codesMapNew[256];
	// initCodesMap(codesMapNew);
	char current[50];
	current[0] = '\0';

	char path[] = "TestingFiles/test.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

	LinkedTree = buildHuffmanTree(LinkedTree);

	// generateCodes(LinkedTree, current, codesMapOld);

	
	// int codesMapSize = getSizeOfCodesMap(codesMapOld);
	// printf("%d\n", codesMapSize);
	// serializeCodesMap(codesMapOld, codesMapSize, "TestingFiles/codesbin.cod");
	// std::map<char, std::string> codesMap;
	// encodeTree2(LinkedTree, current, codesMap);
	// printCodes2(codesMap);
	std::map<char, std::string> codesMapNew;
	std::map<char, std::string> codesMapNew0;
	std::map<char, std::string> last;
	generateCodes2(LinkedTree, codesMapNew0);

	serializeCodesMap2(codesMapNew0, "TestingFiles/codesbin.cod");
	deserializeCodesMap2(codesMapNew, "TestingFiles/codesbin.cod");
	printCodes2(codesMapNew0);


	generateCodes2(LinkedTree, last);
	serializeCodesMap2(last, "TestingFiles/codesbin2.cod");
	deserializeCodesMap2(last, "TestingFiles/codesbin2.cod");
	printCodes2(codesMapNew);
	return 0;
} 
