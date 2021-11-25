#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

bool getGrammarFile(grammar* g, char* input) {
	const char EOL = '\n';
	char c;

	FILE* fp = fopen(input, "r");
	if (!fp) { // File not existing
		perror("Error");
		return false;
		}


	gram_init(g);

	// Read file

	do {
		c = (char)fgetc(fp);


		} while (c != EOF);
		gram_print(g);

		fclose(fp);
		return true;
	}
bool getGrammarCin(grammar* g) {
	return true;
	}