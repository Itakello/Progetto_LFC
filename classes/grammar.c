#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "grammar.h"

void gram_init(grammar* g) {
	g->tot_prods = 0;
	g->tot_voc = 0;
	g->tot_set = 0;
	g->start_s = '-';
	g->type_g = 0;
	}
void prod_add(grammar* g, production p) {
	if (g->tot_prods == PRODS_CAP)
		perror("Too many prods");
	else {
		g->prods[g->tot_prods++] = p;
		addVocSet(g, &p);
		if (g->tot_prods == 1)
			g->start_s = g->prods[0].driver; // First is the SS
		}
	}
void addVocSet(grammar* g, production* p) {
	addSet(g, p->driver);
	for (int i = 0; i < p->tot_body; i++) {
		addVoc(g, p->body[i]);
		addSet(g, p->body[i]);
		}
	}
void addVoc(grammar* g, char c) {
	bool found = false;
	if (is_Term(c) || c == '#') {
		for (int i = 0; i < g->tot_voc; i++) {
			if (g->voc[i] == c) {
				found = true;
				}
			}
		if (!found)
			g->voc[g->tot_voc++] = c;
		}
	}
void addSet(grammar* g, char c) {
	bool found = false;
	for (int i = 0; i < g->tot_set; i++) {
		if (g->set_symb[i] == c) {
			found = true;
			}
		}
	if (!found)
		g->set_symb[g->tot_set++] = c;
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
			if (g->type_g == 0) {
				if (is_nonTerm(p.body[0]))
					if (is_Term(p.body[1]))
						g->type_g = 2;
					else
						perr("Insert a regular grammar", 7);
				if (is_Term(p.body[0]))
					if (is_nonTerm(p.body[1]))
						g->type_g = 1;
					else
						perr("Insert a regular grammar", 7);
				}
			if (g->type_g == 1) {
				if (!is_Term(p.body[0]) || !is_nonTerm(p.body[1]))
					perr("Incorrect right-regular grammar", 8);
				}
			if (g->type_g == 2) {
				if (!is_Term(p.body[0]) || !is_nonTerm(p.body[1]))
					perr("Incorrect left-regular grammar", 8);
				}
			}
		}
	}

void gram_print(grammar* g) {
	printf("Grammar type: ");
	if (g->type_g == 0)
		printf("undefined");
	if (g->type_g == 1)
		printf("right");
	if (g->type_g == 2)
		printf("left");
	printf("\nStarting symbol: %c\n", g->start_s);
	printf("Vocabulary: ");
	for (int i = 0; i < g->tot_voc; i++) {
		printf("%c ", g->voc[i]);
		}
	printf("\nSet_sym: ");
	for (int i = 0; i < g->tot_set; i++) {
		printf("%c ", g->set_symb[i]);
		}
	printf("\nProds:\n");
	for (int i = 0; i < g->tot_prods; i++) {
		prod_print(&g->prods[i]);
		}
	}