#include <stdio.h>
#include <stdlib.h>

#include "finiteAutoma.h"
#include "utility.h"

void fa_init(finiteAutoma* fa) {
	fa->start_state = '-';
	fa->tot_states = 0;
	fa->tot_alpha = 0;
	fa->tot_finstates = 0;
	for (int i = 0; i < STATE_CAP; i++) {
		for (int j = 0; j < ALPHA_CAP; j++) {
			fa->tot_trans[i][j] = 0;
			}
		}
	}

void fa_addGram(finiteAutoma* fa, grammar* g) {
	if (g->type_g == 2) {
		fa_addGramSx(fa, g);
		}
	else
		fa_addGramDx(fa, g);
	}
void fa_addGramSx(finiteAutoma* fa, grammar* g) {
	gram_reverse(g);
	fa_addGramDx(fa, g);
	}
void fa_addGramDx(finiteAutoma* fa, grammar* g) {
	fa->start_state = g->start_s;
	fa_addFinState(fa, '*'); // Add final state

	// Add states
	for (int i = 0; i < g->tot_set; i++) {
		if (is_nonTerm(g->set_symb[i]))
			fa_addState(fa, g->set_symb[i]);
		}
	fa_addState(fa, '*');

	// Add alpha
	for (int i = 0; i < g->tot_voc; i++) {
		//if (is_Term(g->voc[i]))
		fa_addAlpha(fa, g->voc[i]);
		}

	// Add Prods
	for (int i = 0; i < g->tot_prods; i++) {
		if (g->prods[i].tot_body == 1)  // Ex: S -> a
			fa_addProd(fa, g->prods[i].body[0], g->prods[i].driver, '*'); // a, S, *
		else // Ex: S -> aA
			fa_addProd(fa, g->prods[i].body[0], g->prods[i].driver, g->prods[i].body[1]); // a, S, A
		}
	}

void fa_addProd(finiteAutoma* fa, char term, char from_state, char to_state) {
	//printf("T: %c, From: %c, To: %c ", term, from_state, to_state);
	for (int i = 0; i < fa->tot_states; i++) {
		for (int j = 0; j < fa->tot_alpha; j++) {
			if (term == fa->alphabet[j] && from_state == fa->states[i]) {
				//printf("OK %d-%d\n", i, j);
				fa->trans[j][i][fa->tot_trans[j][i]++] = to_state;
				}
			}
		}
	}
void fa_addAlpha(finiteAutoma* fa, char c) {
	bool found = false;
	for (int i = 0; i < fa->tot_alpha; i++) {
		if (fa->alphabet[i] == c) {
			found = true;
			}
		}
	if (!found)
		fa->alphabet[fa->tot_alpha++] = c;
	}

void fa_addState(finiteAutoma* fa, char c) {
	bool found = false;
	for (int i = 0; i < fa->tot_states; i++) {
		if (fa->states[i] == c) {
			found = true;
			}
		}
	if (!found)
		fa->states[fa->tot_states++] = c;
	}
void fa_addFinState(finiteAutoma* fa, char c) {
	bool found = false;
	for (int i = 0; i < fa->tot_finstates; i++) {
		if (fa->fin_states[i] == c) {
			found = true;
			}
		}
	if (!found)
		fa->fin_states[fa->tot_finstates++] = c;
	}

void fa_print(finiteAutoma* fa) {
	//printf("\nTOT states:%d - TOT alpha:%d\n", fa->tot_states, fa->tot_alpha);
	printf("States : ");
	for (int i = 0; i < fa->tot_states; i++) {
		printf("%c ", fa->states[i]);
		}
	printf("\nAlpha : ");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c ", fa->alphabet[i]);
		}
	printf("\n\t");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c\t", fa->alphabet[i]);
		}
	printf("\n");
	for (int i = 0; i < fa->tot_states; i++) {
		printf("%c\t", fa->states[i]);
		for (int j = 0; j < fa->tot_alpha; j++) {
			printf("{");
			for (int k = 0; k < fa->tot_trans[j][i] - 1; k++) {
				printf("%c ", fa->trans[j][i][k]);
				}
			printf("%c}\t", fa->trans[j][i][fa->tot_trans[j][i] - 1]);
			}
		printf("\n");
		}

	}