#include "Utils.h"



int main() {
	// printf("test");

	Node* LinkedTree = NULL;

	int frequencyMap[256];
	char* codesMap[256];
	char current[50];
	current[0] = '\0';
	
	char* path = "/home/peter/stuff/huffman-compressor/testingFiles/1.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

    LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);



    return 0;
}
