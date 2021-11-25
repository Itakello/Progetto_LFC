#include <stdio.h>
#include <stdlib.h>

#include "production.h"

void prod_init(production* p) {
	//printf("Creata prod \n");
	vector_init(&p->driver);
	vector_init(&p->body);
	}
void driver_add(production* p, char* c) {
	vector_add(&p->driver, c);
	//printf("Driver added: %c\n", ((char*)vector_get(&p->driver, vector_total(&p->driver) - 1))[0]);
	//printf("\nSize: %d\n", vector_total(&p->driver));
	}
void body_add(production* p, char* c) {
	vector_add(&p->body, c);
	//printf("Body added: %c\n", ((char*)vector_get(&p->body, vector_total(&p->body) - 1))[0]);
	}
void prod_print(production* p) {
	for (int i = 0; i < vector_total(&p->driver); i++) {
		printf("%c", ((char*)vector_get(&p->driver, i))[0]);
		}
	printf(" -> ");
	for (int i = 0; i < vector_total(&p->body); i++) {
		printf("%c", ((char*)vector_get(&p->body, i))[0]);
		}
	printf("\n");
	}
void prod_delete(production* p) {
	vector_free(&p->driver);
	vector_free(&p->body);
	}