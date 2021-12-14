#ifndef FINITEAUTOMA_H
#define FINITEAUTOMA_H
#define STATE_CAP 50
#define ALPHA_CAP 25
#define TRANSITION_CAP 200

#include "grammar.h"

typedef struct transition {
	char from_state;
	char symbol;
	char to_state;
	} transition;

typedef struct finiteAutoma {
	char start_state;
	char states[STATE_CAP];
	int tot_states;
	char fin_states[STATE_CAP];
	int tot_finstates;
	char alphabet[ALPHA_CAP];
	int tot_alpha;
	transition trans[TRANSITION_CAP];
	int tot_trans;
	} finiteAutoma;

void tr_init(transition*, char from, char sym, char to);
transition get_trans_reverse(const transition*);
void tr_print(const transition*);

void fa_init(finiteAutoma*);
void fa_addGram(finiteAutoma*, grammar*);
void fa_addProd(finiteAutoma*, const transition t);
void fa_print(const finiteAutoma*);
void fa_copy_base(const finiteAutoma* from, finiteAutoma* to);
char fa_get_unused_state(const finiteAutoma*);

#endif