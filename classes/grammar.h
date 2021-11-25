#ifndef GRAMMAR_H
#define GRAMMAR_H
#define PRODS_CAP 20

#include "production.h"
typedef struct grammar {
	char start_s;
	production prods[PRODS_CAP];
	int tot_prods;
	}grammar;

void gram_init(grammar*);
void prod_add(grammar*, production);
void set_startS(grammar*);
void gram_print(grammar*);
void gram_delete(grammar*);

#endif