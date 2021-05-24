#ifndef SDC_FREQUENCYTABLE_H
#define SDC_FREQUENCYTABLE_H

bool generateFrequencyTable(char filePath[], int map[256]) {

	for (int i = 0; i < 256; i++) {
		map[i] = 0;
	}

	FILE* file;
	file = fopen(filePath, "r");

	if (!file) {
		return false;
	}

	char currentChar;
	while ((currentChar = fgetc(file)) != EOF) {
		int current = currentChar;
		map[current]++;
	}

	fclose(file);

	return true;
}


void printFrequencyTable(int map[256]) {
	for (int i = 0; i < 256; i++) {
		if (map[i] != 0)
			printf("%c : %d\n", i, map[i]);
	}
}

#endif //SDC_FREQUENCYTABLE_H