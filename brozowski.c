
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

https://en.wikipedia.org/wiki/DFA_minimization#Brzozowski's_algorithm