#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "..\data_s\vector.h"
#include "production.h"
typedef struct grammar {
	char start_s;
	vector prods;
	}grammar;

void gram_init(grammar*);
void prod_add(grammar*, production*);
void gram_print(grammar*);
void gram_delete(grammar*);

#endif