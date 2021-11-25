#ifndef UTILITY_H
#define UTILITY_H
#define LENGTH_LINE 256

#include "grammar.h"
#include <stdbool.h>

void perr(const char*, int);
bool is_nonTerm(const char);
int parseLine(const char*, production*);
bool getGrammarFile(grammar*, const char*);
bool getGrammarCin(grammar*);

#endif