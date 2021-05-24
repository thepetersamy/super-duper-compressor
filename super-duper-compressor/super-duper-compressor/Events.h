#ifndef SDC_EVENTS_H
#define SDC_EVENTS_H

#include "Utils.h"


int events(int choice, char usersPath[]) {


	// converting c string to cpp string
	std::string fullPath = usersPath;
	std::string baseName;

	size_t lastindex = fullPath.find_last_of(".");

	std::string tmpFilePath = fullPath.substr(0, lastindex) + "tmp.bin";
	std::string codesFilePath = fullPath.substr(0, lastindex) + ".cod";

	if (choice == 1) {


		Node* linkedTree = NULL;
		int frequencyMap[256];
		std::map<char, std::string> codesMap;
		char current[50];
		current[0] = '\0';

		generateFrequencyTable(usersPath, frequencyMap);

		linkedTree = generatePriorityQueue(linkedTree, frequencyMap);

		linkedTree = buildHuffmanTree(linkedTree);

		generateCodes2(linkedTree, codesMap);

		serializeCodesMap2(codesMap, codesFilePath.c_str());

		std::string compressedFilePath = fullPath.substr(0, lastindex) + ".com";

		compressFile(usersPath, compressedFilePath.c_str(), tmpFilePath.c_str(), codesMap);

		printCodes2(codesMap);
	}
	else if (choice == 2) {

		std::map<char, std::string> codesMap;

		deserializeCodesMap2(codesMap, codesFilePath.c_str());

		std::string decompressedResultFilePath = fullPath.substr(0, lastindex) + "D.txt";
		std::string compressedFilePath = fullPath.substr(0, lastindex) + ".com";

		decompressFile(compressedFilePath.c_str(), decompressedResultFilePath.c_str(), tmpFilePath.c_str(), codesMap);
	}

}

void printHelp() {
	printf("\n");
	printf("Usage : compressor <option> <input filename>\n");
	printf("\n");
	printf("OPTIONS:\n");
	printf("  -c\tCompress a given text file\n");
	printf("  -d\tDecompress a given compressed file\n");
	printf("EXAMPLES:\n");
	printf("  compressor -c myFile.txt\n");
	printf("  compressor -d myFile.com\n");
	printf("\n");
	printf("NOTES:\n");
	printf("The given decompressed file will be written as <filename>D.txt");
	printf("\n");
}

#endif //SDC_EVENTS_H
