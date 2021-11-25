#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "production.h"

void prod_init(production* p) {
	p->tot_body = 0;
	p->tot_driver = 0;
	}
void driver_add(production* p, char c) {
	if (p->tot_driver == DRIVER_CAP)
		perr("Too many elems", 3);
	else
		p->driver[p->tot_driver++] = c;
	//printf("D added: %c\n", p->driver[p->tot_driver - 1]);
	}
void body_add(production* p, char c) {
	if (p->tot_body == BODY_CAP) {
		perr("Too many elems", 3);
		}
	else {
		p->body[p->tot_body++] = c;
		}
	//printf("B added: %c\n", p->body[p->tot_body - 1]);
	}
void prod_print(production* p) {
	//printf("%d - %d ", p->tot_driver, p->tot_body);
	for (int i = 0; i < p->tot_driver; i++) {
		printf("%c ", p->driver[i]);
		}
	printf("-> ");
	for (int j = 0; j < p->tot_body; j++) {
		printf("%c ", p->body[j]);
		}
	printf("\n");
	}
void prod_delete(production* p) {
	memset(p->body, 0, BODY_CAP);
	memset(p->driver, 0, DRIVER_CAP);
	p->tot_body = 0;
	p->tot_driver = 0;
	}