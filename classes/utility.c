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

bool is_voc(const char c) {
	if ((c >= 'a') && (c <= 'z'))
		return true;
	if ((c >= 'A') && (c <= 'Z'))
		return true;
	if (c == '#' || c == '|')
		return true;
	return false;
	}

bool is_nonTerm(const char c) {
	return ((c >= 'A') && (c <= 'Z'));
	}

void parseLine(const char* line, production* p) {
	prod_init(p);
	char* del = strstr(line, "->");
	if (del == NULL) {
		perr("No production (->) sign", 1);
		}
	char drivers[LENGTH_LINE], bodyes[LENGTH_LINE];
	int pos = del - line;
	strncpy(drivers, line, pos);
	strncpy(bodyes, line + pos + 3, LENGTH_LINE);
	//printf("|D: %s| |B: %s|\n", drivers, bodyes);
	char* pch;
	pch = strtok(drivers, " ,-");
	bool has_nT = false;
	while (pch != NULL) {
		if (!is_voc(*pch))
			perr("Driver : Not a correct value", 5);
		if (is_nonTerm(*pch))
			has_nT = true;
		if (*pch != ' ' && *pch != '\n' && *pch != '0') {
			driver_add(p, *pch);
			}
		pch = strtok(NULL, " ,.-");
		}
	if (!has_nT) {
		perr("Non-terminal missing in driver", 2);
		}
	pch = strtok(bodyes, " ,-");
	while (pch != NULL) {
		//printf(">%c\n", *pch);
		if (!is_voc(*pch))
			perr("Body : Not a correct value", 5);
		body_add(p, *pch);
		pch = strtok(NULL, " ,.-");
		}
	if (p->tot_driver == 0)
		perr("Insert at least a driver element", 4);
	if (p->tot_body == 0)
		perr("Insert at least a body element", 4);
	}

bool getGrammarFile(grammar* g, const char* input) {
	FILE* file = fopen(input, "r");
	if (!file) { // File not existing
		printf("File non esistente\n");
		return false;
		}
	gram_init(g);
	char line[LENGTH_LINE];

	// Read file
	while (fgets(line, sizeof(line), file)) {
		production p;
		parseLine(line, &p);
		prod_add(g, p);
		}
	fclose(file);
	return true;
	}

bool getGrammarCin(grammar* g) {
	gram_init(g);
	char* line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, stdin)) != 1) {
		production p;
		//printf("%d - %s", read, line);
		parseLine(line, &p);
		prod_add(g, p);
		//prod_print(&p);
		}
	return true;
	}

size_t getline(char** lineptr, size_t* n, FILE* stream) {
	char* bufptr = NULL;
	char* p = bufptr;
	size_t size;
	int c;

	if (lineptr == NULL) {
		return -1;
		}
	if (stream == NULL) {
		return -1;
		}
	if (n == NULL) {
		return -1;
		}
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF) {
		return -1;
		}
	if (bufptr == NULL) {
		bufptr = malloc(128);
		if (bufptr == NULL) {
			return -1;
			}
		size = 128;
		}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL) {
				return -1;
				}
			}
		*p++ = c;
		if (c == '\n') {
			break;
			}
		c = fgetc(stream);
		}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
	}