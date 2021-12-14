#ifndef GRAMMAR_H
#define GRAMMAR_H
#define PRODS_CAP 50
#define VOC_CAP 50+1 // Aggiunta di epsilon
#define SET_SYM_CAP 25+1 // Aggiunta di epsilon

#include "production.h"
typedef struct grammar {
	char start_s;
	production prods[PRODS_CAP];
	int tot_prods;
	char voc[VOC_CAP];
	int tot_voc;
	char set_symb[SET_SYM_CAP];
	int tot_set;
	int type_g; //0 -> Undefined, 1 -> Right-regular, 2 -> Left-regular
	}grammar;

void gram_init(grammar*);
void prod_add(grammar*, const production);
void gram_reverse(grammar*);
void addVocSet(grammar*, const production*);
void checkGrammar(grammar*);
void gram_print(grammar*);

#endif