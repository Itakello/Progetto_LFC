#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"


void perr(const char* strerr, int err) {
	fprintf(stderr, "\033[0;31m%s\033[0m\n", strerr);
	if (err > 0) {
		exit(err);
		}
	}

bool is_nonTerm(const char c) {
	return ((c >= 'A') && (c <= 'Z'));
	}

int parseLine(const char* line, production* p) {
	prod_init(p);
	char* del = strstr(line, "->");
	if (del == NULL) {
		perr("No production (->) sign", 1);
		return 1;
		}
	char drivers[LENGTH_LINE], bodyes[LENGTH_LINE];
	int pos = del - line;
	strncpy(drivers, line, pos - 1);
	strncpy(bodyes, line + pos + 2, LENGTH_LINE);
	char* pch;
	pch = strtok(drivers, " ,-");
	bool has_nT = false;
	while (pch != NULL) {
		if (is_nonTerm(*pch))
			has_nT = true;
		driver_add(p, *pch);
		pch = strtok(NULL, " ,.-");
		}
	if (!has_nT) {
		perr("Non-terminal missing in driver", 2);
		return 2;
		}
	pch = strtok(bodyes, " ,-");
	while (pch != NULL) {
		body_add(p, *pch);
		pch = strtok(NULL, " ,.-");
		}
	return 0;
	}

bool getGrammarFile(grammar* g, const char* input) {
	FILE* file = fopen(input, "r");
	if (!file) { // File not existing
		return false;
		}
	//printf("Doing it\n");
	gram_init(g);
	char line[LENGTH_LINE];

	// Read file
	while (fgets(line, sizeof(line), file)) {
		production p;
		int res = parseLine(line, &p);
		if (res == 0)
			prod_add(g, p);
		else
			return res;
		}

	fclose(file);
	return 0;
	}

bool getGrammarCin(grammar* g) {
	gram_init(g);
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, stdin)) != -1) {
		production p;
		int res = parseLine(line, &p);
		if (res == 0)
			prod_add(g, p);
		else
			return res;
		}
	return true;
	}