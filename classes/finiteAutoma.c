#include <stdio.h>
#include <stdlib.h>

#include "finiteAutoma.h"
#include "utility.h"

void fa_init(finiteAutoma* fa) {
	fa->start_state = '-';
	fa->tot_states = 0;
	fa->tot_alpha = 0;
	fa->tot_finstates = 0;
	for (int i = 0; i < ALPHA_CAP; i++) {
		for (int j = 0; j < STATE_CAP; j++) {
			fa->tot_trans[i][j] = 0;
			}
		}
	}
void fa_addGram(finiteAutoma* fa, grammar* g) {
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
		//prod_print(&g->prods[i]);
		if (g->prods[i].tot_body == 1) // Ex: S -> a
			fa_addProd(fa, g->prods[i].body[0], g->prods[i].driver, '*'); // a, S, *
		else // Ex: S -> aA
			fa_addProd(fa, g->prods[i].body[0], g->prods[i].driver, g->prods[i].body[1]); // a, S, A
		}

	}
void fa_addProd(finiteAutoma* fa, char term, char from_state, char to_state) {
	printf("\nT: %c, From: %c, To: %c ", term, from_state, to_state);
	for (int i = 0; i < fa->tot_alpha; i++) {
		if (term == fa->alphabet[i]) {
			for (int j = 0; j < fa->tot_states; j++) {
				if (from_state == fa->states[j]) {
					fa->trans[i][j][fa->tot_trans[i][j]++] = to_state;
					}
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
	printf("\nTOT states:%d - TOT alpha:%d\n", fa->tot_states, fa->tot_alpha);
	printf("States : ");
	for (int i = 0; i < fa->tot_states; i++) {
		printf("%c ", fa->states[i]);
		}
	printf("Alpha : ");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c ", fa->alphabet[i]);
		}
	printf("\n\t");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c\t", fa->alphabet[i]);
		}
	printf("\n");
	int k = 0;
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c\t", fa->states[k++]);
		for (int j = 0; j < fa->tot_states; j++) {
			for (int p = 0; p < fa->tot_trans[i][j]; p++) {
				printf("%c ", fa->trans[i][j][p]);
				}
			printf("\t");
			}
		printf("\n");
		}
	}