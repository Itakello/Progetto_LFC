#ifndef UTILITY_H
#define UTILITY_H
#define LENGTH_LINE 256

#include <stdbool.h>
#include "grammar.h"
#include "finiteAutoma.h"

void perr(const char*, int);
bool is_voc(const char);
bool is_nonTerm(const char);
bool is_Term(const char);
bool is_epsilon(const char);
void sort(char* word, const int dim);
void swap(char* a, char* b);

void parseLineG(char*, grammar*);
bool getGrammarFile(grammar*, const char*);

void parseLineFA(char*, finiteAutoma*);
bool getAutomaFile(finiteAutoma*, const char*);

#endif