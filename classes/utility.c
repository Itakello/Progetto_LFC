#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "..\data_s\set.h"


void perr(const char* strerr, int err) {
	fprintf(stderr, "\033[0;31mError: %s\033[0m\n", strerr);
	if (err > 0) {
		exit(err);
		}
	}

bool is_voc(const char c) {
	return (is_nonTerm(c) || is_epsilon(c) || is_Term(c));
	}

bool is_nonTerm(const char c) {
	return ((c >= 'A') && (c <= 'Z'));
	}

bool is_Term(const char c) {
	return ((c >= 'a') && (c <= 'z'));
	}

void swap(char* a, char* b) {
	char temp = *a;
	*a = *b;
	*b = temp;
	}

void sort(char* word, const int dim) {
	for (int i = 0; i < dim - 1; i++) {
		for (int j = i + 1; j < dim; j++) {
			if (word[i] > word[j]) {
				swap(&word[i], &word[j]);
				}
			}
		}
	}

bool is_epsilon(const char c) {
	return (c == '#');
	}


void parseLineG(char* line, grammar* g) {
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
		p.driver = driver;
		body_add(&p, pch);
		prod_add(g, p);
		body_delete(&p);
		pch = strtok(NULL, "|");
		}
	}

bool getGrammarFile(grammar* g, const char* input) {
	FILE* file = fopen(input, "r");
	if (!file) { // File not existing
		perr("File inputGrammar.txt not found\n", 1);
		}
	gram_init(g);
	char line[LENGTH_LINE];

	// Read file
	while (fgets(line, sizeof(line), file)) {
		parseLineG(line, g);
		}
	fclose(file);
	return true;
	}


void parseLineFA(char* line, finiteAutoma* fa) {
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	char from = line[0];
	if (fa->start_state == '-')
		fa->start_state = from;
	char* del1 = strstr(line, "-");
	char* del2 = strstr(line, ">");
	if (del1 == NULL || del2 == NULL)
		perr("No (-) OR (>) sign", 1);
	int pos1 = del1 - line;
	char sym = line[pos1 + 1];
	char to[LENGTH_LINE];
	int pos = del2 - line;
	strncpy(to, line + pos + 2, LENGTH_LINE);
	char* pch = strtok(to, "|");
	while (pch != NULL) { // Insertion
		transition t;
		tr_init(&t, from, sym, pch[0]);
		fa_addProd(fa, t);
		pch = strtok(NULL, "|");
		}
	}

bool getAutomaFile(finiteAutoma* fa, const char* input) {
	FILE* file = fopen(input, "r");
	if (!file) { // File not existing
		perr("File inputAutoma.txt not found\n", 1);
		}
	fa_init(fa);
	char line[LENGTH_LINE];
	while (fgets((line), sizeof(line), file)[0] != '-') {
		parseLineFA(line, fa);
		}
	fgets((line), sizeof(line), file);
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	char* pch = strtok(line, " ");
	while (pch != NULL) { // Insertion
		addElement(fa->fin_states, pch[0], &fa->tot_finstates);
		pch = strtok(NULL, " ");
		}
	return true;
	}