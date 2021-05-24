#include "Events.h"


int main(int argc, char* argv[]) {

	if (argc == 1) {
		printHelp();
	}
	else if (argc == 3) {

		if (!strcmp(argv[1], "-c")) {
			events(1, argv[2]);
		}
			
		else if (!strcmp(argv[1], "-d")) {
			events(2, argv[2]);
		}
		else {
			printHelp();
		}
	}
	else {
		printHelp();
	}

	return 0;
}
