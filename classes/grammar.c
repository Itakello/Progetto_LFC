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
			g->start_s = g->prods[0].driver[0]; // First is the SS
		}
	}
void set_startS(grammar* g) {
	g->start_s = g->prods[0].driver[0];
	}
void gram_print(grammar* g) {
	printf("Grammar:\n");
	printf("Starting symbol: %c\n", g->start_s);
	for (int i = 0; i < g->tot_prods; i++) {
		prod_print(&g->prods[i]);
		}
	}
void gram_delete(grammar* g) {
	for (int i = 0; i < g->tot_prods; i++) {
		prod_delete(&g->prods[i]);
		}


	}
