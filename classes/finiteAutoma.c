#include <stdio.h>
#include <stdlib.h>

#include "finiteAutoma.h"
#include "utility.h"
#include "../data_s/set.h"

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
	if (g->type_g == 2)
		gram_reverse(g);
	fa->start_state = g->start_s;
	addElement(fa->fin_states, '*', &fa->tot_finstates);

	// Add states
	for (int i = 0; i < g->tot_set; i++) {
		if (is_nonTerm(g->set_symb[i]))
			addElement(fa->states, g->set_symb[i], &fa->tot_states);
		}
	addElement(fa->states, '*', &fa->tot_states);

	// Add alpha
	for (int i = 0; i < g->tot_voc; i++) {
		addElement(fa->alphabet, g->voc[i], &fa->tot_alpha);
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
	for (int i = 0; i < fa->tot_states; i++) {
		for (int j = 0; j < fa->tot_alpha; j++) {
			if (term == fa->alphabet[j] && from_state == fa->states[i]) {
				addElement(fa->trans[j][i], to_state, &fa->tot_trans[j][i]);
				}
			}
		}
	}

void fa_print(finiteAutoma* fa) {
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