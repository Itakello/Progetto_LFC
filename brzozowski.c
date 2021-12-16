
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

void dfs(const finiteAutoma* fa, bool* visited, int u) {
	//printf("%d\n", u);
	if (visited[u])
		return;
	else {
		visited[u] = true;
		for (int i = 0; i < fa->tot_trans; i++) {
			if (fa->trans[i].from_state == fa->states[u]) {
				for (int j = 0; j < fa->tot_states; j++) {
					if (fa->trans[i].to_state == fa->states[j]) {
						/* printf("To %d: %c", u, fa->states[j]);
						printf(" From %d: %c\n", u, fa->states[u]);
						tr_print(&fa->trans[i]); */
						dfs(fa, visited, j);
						break;
						}
					}



				}
			}
		}
	}
/*
Input : DFA o NFA
Output : NFA reversed
*/
finiteAutoma rev(const finiteAutoma* fa) {
	finiteAutoma fRet;
	fa_init(&fRet);
	// 1 Make initial state as final state
	addElement(fRet.fin_states, fa->start_state, &fRet.tot_finstates);
	// 2 Create a fake initial state and connect all fake initial state with an ɛ-transition
	fRet.start_state = fa_get_unused_stateZ(fa);
	for (int i = 0; i < fa->tot_finstates; i++) {
		transition t;
		tr_init(&t, fRet.start_state, '#', fa->fin_states[i]);
		fa_addProd(&fRet, t);
		}
	// 3 Reverse the edges
	for (int i = 0; i < fa->tot_trans; i++) {
		fa_addProd(&fRet, get_trans_reverse(&fa->trans[i]));
		}
	// fa_print(&fRet);

	// 4 - DFS, find states that doesn't start from the starting state
	bool visited[STATE_CAP];
	memset(visited, false, STATE_CAP);
	for (int i = 0; i < fRet.tot_states; i++) {
		if (fRet.states[i] == fRet.start_state) {
			dfs(&fRet, visited, i);
			}
		}
	/* for (int i = 0; i < STATE_CAP; i++) {
		printf("%d ", visited[i]);
		}
	printf("\n"); */

	// Rimuovi transizioni non visitate
	for (int i = 0; i < fRet.tot_trans; i++) {
		for (int j = 0; j < fRet.tot_states; j++) {
			if (fRet.trans[i].from_state == fRet.states[j] || fRet.trans[i].to_state == fRet.states[j]) {
				if (!visited[j]) {
					removeTrans(fRet.trans, fRet.trans[i], &fRet.tot_trans);
					i--;
					}
				}
			}
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
	// Rimuovi alpha inutilizzati
	for (int j = 0; j < fRet.tot_alpha; j++) {
		bool ok = false;
		for (int i = 0; i < fRet.tot_trans; i++) {
			if (fRet.trans[i].symbol == fRet.alphabet[j])
				ok = true;
			}
		if (!ok)
			removeElement(fRet.alphabet, fRet.alphabet[j], &fRet.tot_alpha);
		}

	return fRet;
	}

// TODO : Quando viene inserito nel DFA è un singolo stato
finiteAutoma det(const finiteAutoma* fa) {
	// Creazione fa
	finiteAutoma fRet;
	fa_init(&fRet);

	// Array per i nomi del DFA
	char names[TRANSITION_CAP];
	int tot_names = 0;

	// 1 stato DFA -> n stati NFA
	char R[TRANSITION_CAP][STATE_CAP];
	int tot_R[TRANSITION_CAP];
	memset(tot_R, 0, sizeof(int) * TRANSITION_CAP);

	// eps_chiusura per T0
	eps_chiusura(R[0], &tot_R[0], fa->start_state, fa);
	sort(R[0], tot_R[0]);
	names[tot_names++] = fa_get_unused_stateA(&fRet);
	addElement(fRet.states, names[0], &fRet.tot_states);
	fRet.start_state = names[0];

	// Print di T0
	/* printf("T0 %c : ", names[0]);
	for (int i = 0; i < tot_R[0]; i++) {
		printf("%c ", R[0][i]);
		}
	printf("\n"); */

	// Unmark T0
	bool marked[TRANSITION_CAP];
	memset(marked, true, sizeof(bool) * TRANSITION_CAP);
	marked[0] = false;
	int curr = 0;

	while (curr != -1) { // -1 means no more to mark
		marked[curr] = true;
		printf("Curr : %d -> ", curr);
		for (int i = 0; i < tot_R[curr]; i++) {
			printf("%c ", R[curr][i]);
			}
		printf("\n");

		for (int i = 0; i < fa->tot_alpha; i++) {
			char a = fa->alphabet[i];
			if (!is_epsilon(a)) {

				// Creo set : tutti gli stati raggiungibili tramite una a-transizione da uno degli stati in t
				char tempSet[STATE_CAP];
				int tot_tempSet = 0;
				for (int j = 0; j < fa->tot_trans; j++) {
					for (int k = 0; k < tot_R[curr]; k++) {
						if (fa->trans[j].from_state == R[curr][k] && fa->trans[j].symbol == a) {

							addElement(tempSet, fa->trans[j].to_state, &tot_tempSet);
							}
						}
					}
				// Print di tempSet
				printf("Print di tempSet %c (%c) : ", names[curr], a);
				for (int j = 0; j < tot_tempSet; j++) {
					printf("%c ", tempSet[j]);
					}
				printf("\n");
				//se ne calcola la ε-chiusura e la si salva nella variabile T1
				if (tot_tempSet > 0) {
					char T1[STATE_CAP];
					int tot_T1 = 0;
					for (int j = 0; j < tot_tempSet; j++) {
						eps_chiusura(T1, &tot_T1, tempSet[j], fa);
						}
					sort(T1, tot_T1);

					// Print di T'
					printf("Print di T1 %c (%c) : ", names[curr], a);
					for (int j = 0; j < tot_T1; j++) {
						printf("%c ", T1[j]);
						}
					printf("\n");

					// Connect to old or new production
					transition t;
					bool found = false;
					for (int j = 0; j < TRANSITION_CAP; j++) {
						if (strcmp(T1, R[j]) == 0) {
							found = true;
							tr_init(&t, names[curr], a, names[j]);
							}
						}
					if (!found) {
						names[tot_names++] = fa_get_unused_stateA(&fRet);
						tr_init(&t, names[curr], a, names[tot_names - 1]);
						}
					fa_addProd(&fRet, t);

					// add T' to R if T' ∉ R
					bool add = true;
					for (int j = 0; j < TRANSITION_CAP; j++) {
						if (strcmp(R[j], T1) == 0)
							add = false;
						}
					if (add) {
						for (int j = 0; j < TRANSITION_CAP; j++) {
							if (tot_R[j] == 0) {
								printf("Adding in pos %d\n", j);
								strcpy(R[j], T1);
								tot_R[j] = strlen(R[j]);
								marked[j] = false;
								break;
								}
							}
						}
					}
				}
			}


		// Select new curr, else -1
		curr = -1;
		for (int i = 0; i < TRANSITION_CAP; i++) {
			if (!marked[i]) {
				marked[i] = false;
				curr = i;
				break;
				}
			}
		}
	// Insert fin states
	for (int i = 0; i < tot_names; i++) {
		for (int j = 0; j < tot_R[i]; j++) {
			if (member(fa->fin_states, R[i][j], fa->tot_finstates))
				addElement(fRet.fin_states, fRet.states[i], &fRet.tot_finstates);
			}
		}

	return fRet;
	}

finiteAutoma brzozowki(const finiteAutoma* fa) {
	finiteAutoma fRet;
	return fRet;
	}
/*
* stack
* array booleano alreadyOn -> segnare se uno stato t è già sulla pila o meno
* array bidimensionale per ricordare move_n
TODO : Sostituire con stack
*/
void eps_chiusura(char* set, int* dim, const char start, const finiteAutoma* fa) {
	bool found = addElement(set, start, dim);
	while (found) {
		found = false;
		for (int i = 0; i < *dim; i++) {
			for (int j = 0; j < fa->tot_trans; j++) {
				if (fa->trans[j].from_state == set[i] && fa->trans[j].symbol == '#') {
					if (addElement(set, fa->trans[j].to_state, dim))
						found = true;
					}
				}
			}
		}
	}