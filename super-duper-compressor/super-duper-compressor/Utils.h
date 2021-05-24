#ifndef SDC_UTILS_H
#define SDC_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <map>
#include "FrequencyTable.h"
#include "LinkedTree.h"


Node* generatePriorityQueue(Node* h, int map[256]) {
	for (int i = 0; i < 256; i++) {
		if (map[i] != 0) {
			h = insertSort(h, map[i], i);
		}
	}
	return h;
}

char* concatenateString(char* str1, const char* str2) {
	int str1Len = strlen(str1);
	int str2Len = strlen(str2);
	int strLen = str1Len + str2Len + 1;

	char* result = (char*)malloc(sizeof(char) * strLen);

	int i;
	for (i = 0; i < str1Len; i++)
		result[i] = str1[i];

	for (int j = 0; j < str2Len; j++, i++)
		result[i] = str2[j];

	result[i] = '\0';


	return result;


}
// copied functions from stackoverflow to faciltate getting basename from path
std::string pathname_directory(const std::string& pathname) {
	std::size_t len = pathname.find_last_of("/\\");
	return len == std::string::npos ? "" : pathname.substr(0, len);
}

std::string pathname_sans_directory(const std::string& pathname) {
	std::size_t len = pathname.find_last_of("/\\");
	return len == std::string::npos ? pathname : pathname.substr(len + 1);
}

// this function was copied from github bc the original strcat 
// wasn't working for some reason
char* strcat2(char* str1, const char* str2) {
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


void initCodesMap(char* codesMap[]) {
	for (int i = 0; i < 256; i++) {
		codesMap[i] = NULL;
	}
}

bool isLeaf(Node* root) {
	return root->left == NULL && root->right == NULL;
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


void encodeTree2(Node* root, std::string currentCode, std::map<char, std::string>& codesMap) {
	if (!root)
		return;


	else if (isLeaf(root)) {
		// codesMap[root->data] = currentCode;
		codesMap.insert(std::pair<char, std::string>(root->data, currentCode));
	}
	encodeTree2(root->left, currentCode + "0", codesMap);
	encodeTree2(root->right, currentCode + "1", codesMap);
}

void printCodes(char* codesMap[]) {
	for (int i = 0; i < 256; i++) {
		if (codesMap[i]) {
			printf("%d : %c : %s\n", i, i, codesMap[i]);
		}
	}
}

void printCodes2(std::map<char, std::string>& codesMap) {

	std::map<char, std::string>::iterator it;

	for (it = codesMap.begin(); it != codesMap.end(); it++) {
		// printf("%c : %s\n", it->first, it->second);
		std::cout << it->first << " : " << it->second << std::endl;
	}
	std::cout << std::endl;
}

void generateCodes(Node* root, char* currentCode, char* codesMap[]) {
	initCodesMap(codesMap);
	encodeTree(root, currentCode, codesMap);
	//printCodes(codesMap);
}


void generateCodes2(Node* root, std::map<char, std::string>& codesMap) {
	std::string currentCode;
	if (!(root->left) && !(root->right)) {
		codesMap.insert(std::pair<char, std::string>(root->data, "0"));
	}
	else {
		encodeTree2(root, currentCode, codesMap);
	}
}


void decToBinary(int n, char result[9]) {
	// array to store binary number
	int binaryNum[8];// = {0};

	for (int i = 0; i < 8; i++) {
		result[i] = '0';
		binaryNum[i] = 0;
	}
	// counter for binary array
	int i = 0;
	while (n > 0) {

		// storing remainder in binary array
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	// printing binary array in reverse order
	for (int j = 7, n = 0; j >= 0; j--, n++) {
		if (binaryNum[n] == 1)
			result[j] = '1';
		else if (binaryNum[n] == 0)
			result[j] = '0';
	}
	result[8] = '\0';
}


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
int convertStrToInt(char str[]) {
	int result = 0;
	for (int i = 0; i < 8; i++) {
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

// now this one we wrote to to just copy one character to a string
void strcat3(char dst[], char src) {
	int len = strlen(dst);
	// printf("len : %d", len);
	dst[len] = src;
	dst[len + 1] = '\0';
}

// the codes are written in a file in the following foramt
// s100
// f011
//  1111
// where every character is followd by its code then a new line
void serializeCodesMap2(std::map<char, std::string>& codesMap, const char* filePath) {

	//clearing content "should be opt in future"
	FILE* file1 = fopen(filePath, "w");
	fclose(file1);

	FILE* file = fopen(filePath, "a");
	std::map<char, std::string>::iterator it;
	for (it = codesMap.begin(); it != codesMap.end(); it++) {
		fprintf(file, "%c%s\n", it->first, it->second.c_str());
	}

	fclose(file);
}


// shift all characters one place to the left 
void shiftLeft(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		str[i] = str[i + 1];
	}
}

void deserializeCodesMap2(std::map<char, std::string>& codesMap, const char* filePath) {
	FILE* file = fopen(filePath, "r");
	char line[256];
	char line2[256];
	char code[30];

	while (fgets(line, 45, file)) {

		// if the first code is a new line, read the code from the next line,
		// as fgets reads until it sees a \n
		if (line[0] == '\n') {
			fgets(line2, 45, file);
			char character = line[0];
			std::string cppStr = line2;
			cppStr[cppStr.length() - 1] = '\0'; // removing the new line from the string
			codesMap.insert(std::pair<char, std::string>(character, cppStr));
		}
		else {
			// taking the first character into a char variable
			char character = line[0];
			shiftLeft(line);
			std::string cppStr = line;
			cppStr[cppStr.length() - 1] = '\0'; // removing the new line from the string
			codesMap.insert(std::pair<char, std::string>(character, cppStr));
		}

	}
	fclose(file);
}


int compressFile(char srcName[], const char* dstName, const char* tmpName, std::map<char, std::string>& codesMap) {
	FILE* src, * tmpFile, * dst;
	src = fopen(srcName, "r");
	if (!src) {
		printf("Cannot read input file");
		return -2;
	}
	tmpFile = fopen(tmpName, "wb+");
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
	while ((currentChar = fgetc(src)) != EOF) {
		fprintf(tmpFile, "%s", codesMap[currentChar].c_str());
	}

	fseek(tmpFile, 0, SEEK_SET);


	//convert to ascii
	int eightNums = ftell(tmpFile) / 8;
	int counter = 0;
	char currentCode[9];
	currentCode[0] = '\0';
	while ((currentChar = fgetc(tmpFile)) != EOF) {
		strcat3(currentCode, currentChar);

		if (++counter % 8 == 0) { //BYT3AML M3AHOM B3D MB2O 8 ASLUN

			int decEq = convertBinToDec(convertStrToInt(currentCode));
			fprintf(dst, "%c", decEq);
			currentCode[0] = '\0';
		}
	}

	fclose(src);
	fclose(dst);
	fclose(tmpFile);
	remove(tmpName);
}


bool isDotCom(const char* path) {
	int len = strlen(path);

	if (path[len - 1] == 'm' && path[len - 2] == 'o' &&
		path[len - 3] == 'c' && path[len - 4] == '.') {
		return 1;
	}
	return 0;
}

int decompressFile(const char* srcName, const char* dstName, const char* tmpName, std::map<char, std::string>& codesMap) {
	FILE* src, * tmpFile, * dst;
	src = fopen(srcName, "rb");
	if (!src) {
		printf("Cannot read input file");
		return -2;
	}

	if (isDotCom(srcName)) {
		printf("Wrong input file, please enter a file that ends with .com\n");
		return 0;
	}

	tmpFile = fopen(tmpName, "wb+");
	if (!tmpFile) {
		printf("Cannot create output file1");
		return -2;
	}
	dst = fopen(dstName, "wb+");
	if (!dst) {
		printf("Cannot create output file2");
		return -2;
	}

	//get the number of the charachters to loop on the compressed file
	fseek(src, 0L, SEEK_END);
	int fileNumbers = ftell(src);
	char currentChar;
	int counter = 0;
	fseek(src, 0L, SEEK_SET);

	while (counter < fileNumbers) { 	//loop on the compressed file with their number of characters
		currentChar = fgetc(src);
		unsigned char digit;
		digit = currentChar; //turn the signed characters to unsigned
		char tempStr[9];
		decToBinary(digit, tempStr); //convert to binary
		fprintf(tmpFile, "%s", tempStr); //then put them in the temp file to decompress
		counter++;
	}

	fseek(tmpFile, 0, SEEK_SET);
	char currentCode[8];
	for (int i = 0; i < 8; i++) { //read number of zeros 
		currentCode[i] = fgetc(tmpFile);
	}
	int numZeros = convertBinToDec(convertStrToInt(currentCode)); //convert string to integer so we can convert binary to decimal 
	for (int i = 0; i < numZeros; i++) { //make a loop on the extra zeros so we start reading after the zeros
		currentChar = fgetc(tmpFile);
	}

	fseek(tmpFile, 0, SEEK_CUR); // start writing from the location of pointer that read

	std::string currentCode1;
	while ((currentChar = fgetc(tmpFile)) != EOF) {
		std::map<char, std::string>::iterator it; // try moving up
		currentCode1 += currentChar;
		for (it = codesMap.begin(); it != codesMap.end(); it++) {
			std::string code = it->second.c_str();
			if (currentCode1 == code) {
				char x = it->first;
				if (x == '\n') {
					fprintf(dst, "\r", x);
				}
				fprintf(dst, "%c", x);
				currentCode1.clear(); // try opt hena

				break;
			}
		}
	}

	fclose(src);
	fclose(dst);
	fclose(tmpFile);
	remove(tmpName);
}

#endif //SDC_UTILS_H
