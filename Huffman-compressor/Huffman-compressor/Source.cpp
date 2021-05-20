#include "Utils.h"
	// currentCode1+currentChar;
		// for (int i = 0; i < 256; i++) {
		// 	// std::cout<<codesMap[i]<<std::endl;
		// 	if (codesMap[i] == currentCode1) {
		// 		printf("%c : %d", i, i);
		// 		fprintf(dst, "%c", i);
		// 		currentCode1.clear();
		// 		break;
		// 	}	
		// }

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
int decToBinary(int n, char result[9])
{
	// array to store binary number
	int binaryNum[8] = {0};

	for (int i = 0; i < 8; i++)
	{
		result[i] = '0';
	}
	// counter for binary array
	int i = 0;
	while (n > 0)
	{

		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	// printing binary array in reverse order
	for (int j = 7, n = 0; j >= 0; j--, n++)
	{
		if (binaryNum[n] == 1)
			result[j] = '1';
		else if (binaryNum[n] == 0)
			result[j] = '0';
	}
	result[8] = '\0';
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
	for (it = codesMap.begin(); it != codesMap.end(); it++)
	{
		// printf("%c : %s\n", it->first, it->second);
		// std::cout<<it->first<<it->second<<std::endl;

		// printf("%c", it->first);
		fprintf(file, "%c%s\n", it->first, it->second.c_str());

		// for(int i=0; it->second[i] != '\0'; i++){
		// 	// printf("%c", it->second[i]);
		// 	fprintf(file, "%c", it->second[i]);
		// }
		// fprintf(file, "\n");

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

void deserializeCodesMap2(std::map<char, std::string> &codesMap, const char *filePath)
{
	FILE *file = fopen(filePath, "r");
	char line[256];
	char line2[256];
	char code[30];
	
	while (fgets(line, 45, file)){
		if(line[0] == '\n'){
			fgets(line2,45, file);
			char character = line[0];
			std::string cppStr = line2;
			// std::string c = codesMap[character];
			cppStr[cppStr.length() -1] = '\0';
			codesMap.insert(std::pair<char,std::string>(character, cppStr));
			// std::cout<<character<<" : "<<cppStr<<std::endl;
			// printf("line = %c : %s\n", character, line2);

		}
		else{
			char character = line[0];
			shiftLeft(line);
			std::string cppStr = line;
			// printf("LEN : %d", cppStr.length());
			cppStr[cppStr.length() -1] = '\0';
			codesMap.insert(std::pair<char,std::string>(character, cppStr));
			// std::cout<<character<<" : "<<cppStr<<std::endl;

			// printf("line = %c : %s\n", character, line);
		}

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
int convertBinToDec(int n)
{
	int dec = 0, i = 0, rem;
	while (n != 0)
	{
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2, i);
		++i;
	}
	return dec;
}
int convertStrToInt(char str[])
{
	int result = 0;
	for (int i = 0; i < 8; i++)
	{
		result = result * 10 + (str[i] - '0');
	}
	return result;
}
void strcat3(char dst[], char src)
{
	int len = strlen(dst);
	// printf("len : %d", len);
	dst[len] = src;
	dst[len + 1] = '\0';
}
int compress(char srcName[], char dstName[], char *codesMap[])
{
	FILE *src, *tmpFile, *dst;
	src = fopen(srcName, "r");
	if (!src)
	{
		printf("Cannot read input file");
		return -2;
	}

	tmpFile = fopen("TestingFiles/tmp.bin", "wb+");
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

	//convertBinToDec from codesMap[] to 0/1
	while ((currentChar = fgetc(src)) != EOF)
	{
		fprintf(tmpFile, "%s", codesMap[currentChar]);
	}

	int totalFileBits;
	totalFileBits = ftell(tmpFile); //total numbers in file

	fseek(tmpFile, 0, SEEK_SET); //to start from the begining

	//extra zeros
	int extraZeros;
	extraZeros = 8 - (totalFileBits % 8);

	char tmpStr[9];
	decToBinary(extraZeros, tmpStr);
	fprintf(tmpFile, "%s", tmpStr);
	for (int i = 0; i < extraZeros; i++)
		fprintf(tmpFile, "0");

	fseek(src, 0, SEEK_SET);

	//reconvert src from codesMap[] after current zeros
	while ((currentChar = fgetc(src)) != EOF)
	{
		fprintf(tmpFile, "%s", codesMap[currentChar]);
	}

	fseek(tmpFile, 0, SEEK_SET);

	//convert to ascii
	int eightNums = ftell(tmpFile) / 8;
	int counter = 0;
	char currentCode[8];
	currentCode[0] = '\0';
	while ((currentChar = fgetc(tmpFile)) != EOF)
	{
		// char currentCharStr[2];
		// currentCharStr[0] = currentChar;
		// currentCharStr[1] = '\0';
		// strcat(currentCode, currentCharStr);
		// printf("%s", currentCharStr);
		// printf("code : %s\n", currentCode);
		// printf("%c", currentChar);
		strcat3(currentCode, currentChar);

		if (++counter % 8 == 0)
		{ //BYT3AML M3AHOM B3D MB2O 8 ASLUN

			// printf("%s\n", currentCode);
			int decEq = convertBinToDec(convertStrToInt(currentCode));
			// printf("dec : %d\n", decEq);
			fprintf(dst, "%c", decEq);
			currentCode[0] = '\0';
		}
	}
	remove("TestingFiles/tmp.bin");

	fclose(src);
	fclose(dst);
	fclose(tmpFile);
}
int compress2(char srcName[], char dstName[], std::map<char, std::string> &codesMap)
{
	FILE *src, *tmpFile, *dst;
	src = fopen(srcName, "r");
	if (!src) {
		printf("Cannot read input file");
		return -2;
	}
	tmpFile = fopen("TestingFiles/tmp.bin", "wb+");
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
	//convertBinToDec from codesMap[] to 0/1
	while ((currentChar = fgetc(src)) != EOF) {
		
		// printf("%c : %s",currentChar, codesMap[currentChar].c_str());
		fprintf(tmpFile, "%s", codesMap[currentChar].c_str());
	}

	int totalFileBits;
	totalFileBits = ftell(tmpFile); //total numbers in file

	fseek(tmpFile, 0, SEEK_SET); //to start from the begining

	//extra zeros
	int extraZeros;
	extraZeros = 8 - (totalFileBits % 8);


	char tmpStr[9];
	decToBinary(extraZeros, tmpStr);
	fprintf(tmpFile, "%s", tmpStr);
	for (int i = 0; i < extraZeros; i++)		
		fprintf(tmpFile, "0");

	fseek(src, 0, SEEK_SET);

	//reconvert src from codesMap[] after current zeros
	while ((currentChar = fgetc(src)) != EOF)
	{
		fprintf(tmpFile, "%s", codesMap[currentChar].c_str());
	}

	fseek(tmpFile, 0, SEEK_SET);

	
	//convert to ascii
	int eightNums = ftell(tmpFile) / 8;
	int counter = 0;
	char currentCode[8];
	currentCode[0] = '\0';
	while ((currentChar = fgetc(tmpFile)) != EOF)
	{
		// char currentCharStr[2];
		// currentCharStr[0] = currentChar;
		// currentCharStr[1] = '\0';
		// strcat(currentCode, currentCharStr);
		// printf("%s", currentCharStr);
		// printf("code : %s\n", currentCode);
		// printf("%c", currentChar);
		strcat3(currentCode, currentChar);

		if (++counter % 8 == 0)
		{ //BYT3AML M3AHOM B3D MB2O 8 ASLUN

			// printf("%s\n", currentCode);
			int decEq = convertBinToDec(convertStrToInt(currentCode));
			// printf("dec : %d\n", decEq);
			fprintf(dst, "%c", decEq);
			currentCode[0] = '\0';
		}
	}
	// remove("TestingFiles/tmp.bin");

	fclose(src);
	fclose(dst);
	fclose(tmpFile);
}

int decompress1(char srcName[], char dstName[], std::map<char, std::string> &codesMap)
{
	FILE *src, *tmpFile, *dst;
	src = fopen(srcName, "rb");
	if (!src) {
		printf("Cannot read input file");
		return -2;
	}

	tmpFile = fopen("TestingFiles/tmp2.bin", "wb+");
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
	while ((currentChar = fgetc(src)) != EOF){
		unsigned char digit;
		digit = currentChar;
		char tempStr[9];
		tempStr[9] = '\0';
		decToBinary(digit, tempStr);
		// printf("%s", tempStr);
		fprintf(tmpFile, "%s", tempStr);
	}

	fseek(tmpFile, 0, SEEK_SET);
	char currentCode[8];
	for (int i = 0; i < 8; i++)
	{
		currentCode[i] = fgetc(tmpFile);
	}
	int numZeros = convertBinToDec(convertStrToInt(currentCode));
	for (int i = 0; i < numZeros; i++)
	{
		currentChar = fgetc(tmpFile);
	}

	fseek(tmpFile, 0, SEEK_CUR);

	std::string currentCode1;
	while ((currentChar = fgetc(tmpFile)) != EOF){
		std::map<char, std::string>::iterator it;
		currentCode1+=currentChar;
		for(it = codesMap.begin(); it != codesMap.end(); it++){
			std::string code = it->second.c_str();
			bool res = currentCode1 == code;
			// std::cout<<"comparing : "<<currentCode1<<"     "<<code<<"   result : "<<res<<std::endl;
			if (currentCode1 == code) {
				fprintf(dst, "%c", it->first);
				// std::cout<<"character : "<<it->first<<std::endl;
				currentCode1.clear();
				// break;
			}
		}
		// std::cout<<std::endl;
	}

	fclose(src);
	fclose(dst);
	fclose(tmpFile);
}

int main()
{
	

	Node *LinkedTree = NULL;

	int frequencyMap[256];
	char *codesMapOld[256];
	// char *codesMapNew[256];
	// initCodesMap(codesMapNew);
	char current[50];
	current[0] = '\0';

	char path[] = "TestingFiles/1.txt";
	char path2[] = "TestingFiles/out.com";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

	LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMapOld);

	int codesMapSize = getSizeOfCodesMap(codesMapOld);
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
	// printCodes2(codesMapNew0);
	
	deserializeCodesMap2(codesMapNew, "TestingFiles/codesbin.cod");
	// printCodes2(codesMapNew);

	compress2(path, "TestingFiles/out.com",codesMapNew);

	// generateCodes(LinkedTree, current, codesMapOld);
	// compress(path, path2, codesMapOld);
	decompress1(path2, "TestingFiles/2_d.txt", codesMapNew);
	return 0;
}
