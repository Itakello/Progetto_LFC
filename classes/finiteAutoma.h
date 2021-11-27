#ifndef FINITEAUTOMA_H
#define FINITEAUTOMA_H
#define STATE_CAP 50
#define ALPHA_CAP 25

#include "grammar.h"

typedef struct finiteAutoma {
	char start_state;
	char states[STATE_CAP];
	int tot_states;
	char fin_states[STATE_CAP];
	int tot_finstates;
	char alphabet[ALPHA_CAP];
	int tot_alpha;
	char trans[STATE_CAP][ALPHA_CAP][STATE_CAP];
	int tot_trans[STATE_CAP][ALPHA_CAP];
	} finiteAutoma;

void fa_init(finiteAutoma*);
void fa_addGram(finiteAutoma*, grammar*);
void fa_addProd(finiteAutoma*, char, char, char);
void fa_addAlpha(finiteAutoma*, char);
void fa_addState(finiteAutoma*, char);
void fa_addFinState(finiteAutoma*, char);
void fa_print(finiteAutoma*);

#endif