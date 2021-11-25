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

	// Read file
	gram_init(g);
	production p1;
	prod_init(&p1);
	driver_add(&p1, "S");
	body_add(&p1, "#");
	prod_add(g, &p1);
	/* do 	{
		c = (char)fgetc(fp);


		} while (c != EOF); */

	fclose(fp);
	return true;
	}
bool getGrammarCin(grammar* g) {
	return true;
	}