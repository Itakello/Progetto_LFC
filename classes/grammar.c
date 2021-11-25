#include <stdio.h>
#include <stdlib.h>

#include "grammar.h"

void gram_init(grammar* g) {
	vector_init(&g->prods);
	}
void prod_add(grammar* g, production* p) {
	vector_add(&g->prods, p);
	if (vector_total(&g->prods) == 1)
		set_startS(g);
	//printf("Added: ");prod_print(p);
	}
void set_startS(grammar* g) {
	production* p = (production*)vector_get(&g->prods, 0);
	g->start_s = ((char*)vector_get(&p->driver, 0))[0];
	}
void gram_print(grammar* g) {
	printf("Starting symbol: %c\n", g->start_s);
	for (int i = 0; i < vector_total(&g->prods); i++) {
		prod_print((production*)vector_get(&g->prods, i));
		}
	}
void gram_delete(grammar* g) {
	vector_free(&g->prods);
	}
