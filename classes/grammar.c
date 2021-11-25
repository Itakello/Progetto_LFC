#include <stdio.h>
#include <stdlib.h>

#include "grammar.h"

void gram_init(grammar* g) {
	vector_init(&g->prods);
	}
void prod_add(grammar* g, production* p) {
	vector_add(&g->prods, p);
	//printf("Added: ");prod_print(p);
	}
void gram_print(grammar* g) {
	for (int i = 0; i < vector_total(&g->prods); i++) {
		prod_print((production*)vector_get(&g->prods, i));
		}
	}
void gram_delete(grammar* g) {
	vector_free(&g->prods);
	}
