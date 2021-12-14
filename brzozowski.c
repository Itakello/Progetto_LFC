
// DFA minimzation following Brzozowski

/*
Assume a more general definition regards DFAs, beacuse instead of a single initial state, there could be more of them (the first step in the subset construction is the epsilon-closure of all initial states)

Input : DFA o NFA
Output : Minimal DFA

LEGENDA :
* A -> automaton
* det -> subset contruction method
* rev -> procedure that computes an NFA tha accepts L(A)^R
NOTE : rev can be applied to any finite automaton
NOTE 2 : It doesn't utilize determinism
*/

/* DFA brzozowski(FiniteAutoma fa) {
	return det(rev(det(rev(fa))))
	} */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "brzozowski.h"
#include "data_s\set.h"

void dfs(const finiteAutoma* fa, bool* visited, char c, int u) {
	if (visited[u])
		return;
	else {
		visited[u] = true;
		for (int i = 0; i < fa->tot_trans; i++) {
			if (fa->trans[i].from_state == c) {
				dfs(fa, visited, i, fa->trans[i].to_state);
				}
			}
		}
	}
/*
* Make initial state as final state
* Create a fake initial state and connect all fake initial state with an ɛ-transition
* Reverse the edges
* Remove the inappropriate transition state.
Input : DFA o NFA
Output : NFA reversed
*/
finiteAutoma rev(const finiteAutoma* fa) {
	finiteAutoma fRet;
	fa_init(&fRet);
	// 1
	addElement(fRet.fin_states, fa->start_state, &fRet.tot_finstates);
	// 2
	fRet.start_state = fa_get_unused_state(fa);
	for (int i = 0; i < fa->tot_finstates; i++) {
		transition t;
		tr_init(&t, fRet.start_state, '#', fa->fin_states[i]);
		fa_addProd(&fRet, t);
		}
	// 3
	for (int i = 0; i < fa->tot_trans; i++) {
		fa_addProd(&fRet, get_trans_reverse(&fa->trans[i]));
		}
	// 4 - DFS, find states that doesn't start from the starting state
	/* bool* visited;
	visited = (bool*)calloc(fa->tot_trans, sizeof(bool));
	if (visited == NULL) {
		perr("Errer! Memory not allocated", 10);
		}
	int startPos = -1;
	for (int i = 0; i < fRet.tot_states; i++) {
		if (fRet.states[i] == fRet.start_state)
			startPos = i;
		}

	dfs(&fRet, visited, fRet.start_state, startPos);

	// Rimuovi transizioni non visitate
	for (int i = 0; i < fRet.tot_trans; i++) {
		if (!visited[i])
			removeTrans(fRet.trans, fRet.trans[i], &fRet.tot_trans);
		}
	// Rimuovi stati inutilizzati
	for (int i = 0; i < fRet.tot_states; i++) {
		bool ok = false;
		for (int j = 0; j < fRet.tot_trans; j++) {
			if (fRet.states[i] == fRet.trans[j].from_state || fRet.states[i] == fRet.trans[j].to_state)
				ok = true;
			}
		if (!ok)
			removeElement(fRet.states, fRet.states[i], &fRet.tot_states);
		}


	free(visited); */

	return fRet;
	}

finiteAutoma det(const finiteAutoma* fa) {

	}

finiteAutoma brzozowki(const finiteAutoma* fa) {

	}