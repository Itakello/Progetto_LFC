#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "production.h"

void set_driver(production* p, char c) {
	p->driver = c;
	}
void body_add(production* p, const char* c) {
	int len = strlen(c);
	int pos = 0;
	for (int i = 0; i < len; i++) {
		if (is_voc(c[i])) {
			p->body[pos++] = c[i];
			p->tot_body++;
			}
		}
	}
void body_delete(production* p) {
	p->tot_body = 0;
	}
void prod_print(production* p) {
	printf("%c -> ", p->driver);
	for (int j = 0; j < p->tot_body; j++) {
		printf("%c ", p->body[j]);
		}
	printf("\n");
	}