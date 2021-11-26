#ifndef UTILITY_H
#define UTILITY_H
#define LENGTH_LINE 256

#include "grammar.h"
#include <stdbool.h>

void perr(const char*, int);
bool is_voc(const char);
bool is_nonTerm(const char);
bool is_Term(const char);
bool is_epsilon(const char);
void parseLine(char*, grammar*);
bool getGrammarFile(grammar*, const char*);
bool getGrammarCin(grammar*);
size_t getline(char**, size_t*, FILE*);

#endif