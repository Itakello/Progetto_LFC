#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "grammar.h"

void gram_init(grammar* g) {
	g->tot_prods = 0;
	g->start_s = '-';
	}
void prod_add(grammar* g, production p) {
	if (g->tot_prods == PRODS_CAP)
		perror("Too many prods");
	else {
		g->prods[g->tot_prods++] = p;
		if (g->tot_prods == 1)
			g->start_s = g->prods[0].driver; // First is the SS
		}
	}
void checkGrammar(grammar* g) {
	for (int i = 0; i < g->tot_prods; i++) {
		production p = g->prods[i];
		if (!is_voc(p.driver))
			perr("Driver : Not a correct value", 5);
		if (!is_nonTerm(p.driver))
			perr("Driver : Not a non-terminal", 6);
		for (int j = 0; j < p.tot_body; j++) {
			if (!is_voc(p.body[j]))
				perr("Body : Not a correct value", 5);
			}
		if (p.tot_body == 0)
			perr("Insert at least 1 body element", 4);
		if (p.tot_body == 1)
			if (!is_epsilon(p.body[0]) && !is_Term(p.body[0])) // A-># o A->a...z
				perr("Insert a regular grammar", 7);
		if (p.tot_body == 2) {
			if (is_nonTerm(p.body[0]) && !is_Term(p.body[1]))
				perr("Insert a regular grammar", 7);
			if (is_Term(p.body[0]) && !is_nonTerm(p.body[1]))
				perr("Insert a regular grammar", 7);
			}
		}

	}
void gram_print(grammar* g) {
	printf("Grammar:\n");
	printf("Starting symbol: %c\n", g->start_s);
	for (int i = 0; i < g->tot_prods; i++) {
		prod_print(&g->prods[i]);
		}
	}