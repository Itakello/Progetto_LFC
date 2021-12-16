#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "finiteAutoma.h"
#include "../data_s/set.h"

void tr_init(transition* t, char from, char sym, char to) {
	t->from_state = from;
	t->symbol = sym;
	t->to_state = to;
	}

transition get_trans_reverse(const transition* t) {
	transition ret;
	ret.from_state = t->to_state;
	ret.to_state = t->from_state;
	ret.symbol = t->symbol;
	return ret;
	}

void tr_print(const transition* t) {
	printf("%c -(%c)> %c\n", t->from_state, t->symbol, t->to_state);
	}

void fa_init(finiteAutoma* fa) {
	fa->start_state = '-';
	fa->tot_states = 0;
	fa->tot_alpha = 0;
	fa->tot_finstates = 0;
	fa->tot_trans = 0;
	}

void fa_addGram(finiteAutoma* fa, grammar* g) {
	if (g->type_g == 2)
		gram_reverse(g);
	fa->start_state = g->start_s;

	// Add Prods
	for (int i = 0; i < g->tot_prods; i++) {
		transition t;
		if (g->prods[i].tot_body == 1)  // Ex: S -> a
			tr_init(&t, g->prods[i].driver, g->prods[i].body[0], '@'); // S, a, Z
		else // Ex: S -> aA
			tr_init(&t, g->prods[i].driver, g->prods[i].body[0], g->prods[i].body[1]); // S, a, A
		fa_addProd(fa, t);
		}
	// Select final state
	char c = fa_get_unused_stateZ(fa);
	addElement(fa->fin_states, c, &fa->tot_finstates);
	addElement(fa->states, c, &fa->tot_states);
	// Swap with the @ final state
	for (int i = 0; i < fa->tot_trans; i++) {
		if (fa->trans[i].to_state == '@')
			fa->trans[i].to_state = c;
		}
	// Remove the @ final state
	removeElement(fa->states, '@', &fa->tot_states);
	}

void fa_addProd(finiteAutoma* fa, const transition t) {
	//tr_print(&t);
	addTrans(fa->trans, t, &fa->tot_trans);
	addElement(fa->alphabet, t.symbol, &fa->tot_alpha);
	addElement(fa->states, t.from_state, &fa->tot_states);
	addElement(fa->states, t.to_state, &fa->tot_states);
	sort(fa->states, fa->tot_states);
	}

char fa_get_unused_stateA(const finiteAutoma* fa) {
	for (char i = 'A'; i <= 'Z'; i++) {
		if (!member(fa->states, i, fa->tot_states))
			return i;
		}
	return '-';
	}

char fa_get_unused_stateZ(const finiteAutoma* fa) {
	for (char i = 'Z'; i >= 'A'; i--) {
		if (!member(fa->states, i, fa->tot_states))
			return i;
		}
	return '-';
	}

void fa_print(const finiteAutoma* fa) {
	printf("\n\t\tFinite Automa\n");
	printf("States : ");
	for (int i = 0; i < fa->tot_states; i++) {
		printf("%c ", fa->states[i]);
		}
	printf("\nStart state : %c", fa->start_state);
	printf("\nFin states : ");
	for (int i = 0; i < fa->tot_finstates; i++) {
		printf("%c ", fa->fin_states[i]);
		}
	printf("\nAlpha : ");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c ", fa->alphabet[i]);
		}
	// Print alphabet
	printf("\n\t\t");
	for (int i = 0; i < fa->tot_alpha; i++) {
		printf("%c\t\t", fa->alphabet[i]);
		}
	printf("\n");
	// Print table
	for (int i = 0; i < fa->tot_states; i++) {
		for (int j = 0; j < fa->tot_finstates; j++) {
			if (fa->states[i] == fa->fin_states[j])
				printf(">");
			}
		if (fa->states[i] != fa->start_state)
			printf("%c\t\t", fa->states[i]);
		else
			printf("%c>\t\t", fa->states[i]);
		for (int j = 0; j < fa->tot_alpha; j++) {
			printf("{");
			int count = 0;
			for (int k = 0; k < fa->tot_trans; k++) {
				if (fa->states[i] == fa->trans[k].from_state && fa->alphabet[j] == fa->trans[k].symbol) {
					printf("%c ", fa->trans[k].to_state);
					count++;
					}
				}
			if (count > 0)
				printf("\b");
			if (count >= 4)
				printf("}\t");
			else
				printf("}\t\t");
			}
		printf("\n");
		}
	}