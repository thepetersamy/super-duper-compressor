#include "Utils.h"



int main() {

	Node* LinkedTree = NULL;

	int frequencyMap[256];
	char* codesMap[256];
	char current[50];
	
	char* path = "/home/peter/stuff/huffman-compressor/test.txt";

	generateFrequencyTable(path, frequencyMap);

	LinkedTree = generatePriorityQueue(LinkedTree, frequencyMap);

    LinkedTree = buildHuffmanTree(LinkedTree);

	generateCodes(LinkedTree, current, codesMap);

	
    return 0;
}
