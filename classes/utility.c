#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"


void perr(const char* strerr, int err) {
	fprintf(stderr, "\033[0;31mError: %s\033[0m\n", strerr);
	if (err > 0) {
		exit(err);
		}
	}

bool is_voc(const char c) {
	if ((c >= 'a') && (c <= 'z'))
		return true;
	if ((c >= 'A') && (c <= 'Z'))
		return true;
	if (c == '#')
		return true;
	return false;
	}

bool is_nonTerm(const char c) {
	return ((c >= 'A') && (c <= 'Z'));
	}
bool is_Term(const char c) {
	return ((c >= 'a') && (c <= 'z'));
	}
bool is_epsilon(const char c) {
	return (c == '#');
	}

void parseLine(char* line, grammar* g) {
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	char driver = line[0];
	char* del = strstr(line, "->");
	if (del == NULL) {
		perr("No production (->) sign", 1);
		}
	char bodyes[LENGTH_LINE];
	int pos = del - line;
	strncpy(bodyes, line + pos + 2, LENGTH_LINE);
	if (line[1] != ' ' || pos != 2)
		perr("Driver : too many values or no space between the driver and ->", 2);
	char* pch = strtok(bodyes, "|");
	while (pch != NULL) { // Insertion
		production p;
		set_driver(&p, driver);
		body_add(&p, pch);
		prod_add(g, p);
		body_delete(&p);
		pch = strtok(NULL, "|");
		}
	}

bool getGrammarFile(grammar* g, const char* input) {
	FILE* file = fopen(input, "r");
	if (!file) { // File not existing
		printf("File %s not found\n", input);
		return false;
		}
	gram_init(g);
	char line[LENGTH_LINE];

	// Read file
	while (fgets(line, sizeof(line), file)) {
		parseLine(line, g);
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
		parseLine(line, g);
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