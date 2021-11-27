#include <stdio.h>
#include <stdlib.h>

#include "finiteAutoma.h"
#include "utility.h"

void fa_init(finiteAutoma* fa) {
	fa->start_state = '-';
	fa->tot_states = 0;
	fa->tot_alpha = 0;
	fa->tot_finstates = 0;
	}
void fa_addGram(finiteAutoma* fa, grammar* g) {
	fa->start_state = g->start_s;
	fa_addFinState(fa, '*');
	fa_addState(fa, fa->start_state); // Add start state
	}
void fa_addState(finiteAutoma* fa, char c) {
	bool found = false;
	if (is_nonTerm(c)) { // ? Da togliere?
		for (int i = 0; i < fa->tot_states; i++) {
			if (fa->states[i] == c) {
				found = true;
				}
			}
		if (!found)
			fa->states[fa->tot_states++] = c;
		}
	}
void fa_addFinState(finiteAutoma* fa, char c) {
	bool found = false;
	if (is_nonTerm(c)) { // ? Da togliere?
		for (int i = 0; i < fa->tot_finstates; i++) {
			if (fa->fin_states[i] == c) {
				found = true;
				}
			}
		if (!found)
			fa->fin_states[fa->tot_finstates++] = c;
		}
	}