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
	} finiteAutoma;

void fa_init(finiteAutoma*);
void fa_addGram(finiteAutoma*, grammar*);
void fa_addState(finiteAutoma*, char);
void fa_addFinState(finiteAutoma*, char);

#endif