#ifndef GRAMMAR_H
#define GRAMMAR_H
#define PRODS_CAP 20
#define VOC_CAP 50+1 // Aggiunta di epsilon
#define SET_SYM_CAP 25+1 // Aggiunta di epsilon

#include "production.h"
typedef struct grammar {
	char start_s;
	production prods[PRODS_CAP];
	char voc[VOC_CAP];
	char set_symb[SET_SYM_CAP];
	int tot_prods;
	}grammar;

void gram_init(grammar*);
void prod_add(grammar*, production);
void set_startS(grammar*);
void checkGrammar(grammar*);
void gram_print(grammar*);
void gram_delete(grammar*);

#endif