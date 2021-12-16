#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "grammar.h"
#include "../data_s/set.h"

void gram_init(grammar* g) {
	g->tot_prods = 0;
	g->tot_voc = 0;
	g->tot_set = 0;
	g->type_g = 0; // Undefined
	g->start_s = '-';
	}

void prod_add(grammar* g, const production p) {
	if (g->tot_prods == PRODS_CAP)
		perror("Too many prods");
	else {
		g->prods[g->tot_prods++] = p;
		addVocSet(g, &p);
		if (g->tot_prods == 1)
			g->start_s = g->prods[0].driver; // First is the SS
		}
	}

void gram_reverse(grammar* g) {
	for (int i = 0; i < g->tot_prods; i++) {
		prod_reverse(&g->prods[i]);
		}
	g->type_g = 1;
	}

void addVocSet(grammar* g, const production* p) {
	addElement(g->set_symb, p->driver, &g->tot_set);
	for (int i = 0; i < p->tot_body; i++) {
		if (is_Term(p->body[i]) || is_epsilon(p->body[i]))
			addElement(g->voc, p->body[i], &g->tot_voc);
		addElement(g->set_symb, p->body[i], &g->tot_set);
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
						perr("Incorrect full right-regular grammar", 8);
					}
				if (g->type_g == 2) {
					if (!is_nonTerm(p.body[0]) || !is_Term(p.body[1]))
						perr("Incorrect full left-regular grammar", 8);
					}
				}
			if (p.tot_body > 2)
				perr("Too many elements in one body", 9);
			}
		}
	}

void gram_print(grammar* g) {
	printf("\n\t\tGrammar\n");
	printf("Grammar type: ");
	if (g->type_g == 0)
		printf("undefined");
	if (g->type_g == 1)
		printf("right");
	if (g->type_g == 2)
		printf("left");
	printf("\nStarting symbol: %c", g->start_s);
	printf("\nVocabulary: ");
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