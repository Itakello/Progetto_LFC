#include <stdio.h>
#include "classes/utility.h"
#include "classes/grammar.h"

int main(int argc, char const* argv[]) {

	grammar g;
	if (!getGrammarFile(&g, "input.txt")) {
		getGrammarCin(&g);
		}
	//gram_print(&g);


	/* production p1, p2, p3;
	prod_init(&p1);
	prod_init(&p2);
	prod_init(&p3);

	driver_add(&p1, "S");
	body_add(&p1, "a");
	body_add(&p1, "A");
	body_add(&p1, "b");
	//prod_print(&p1);
	driver_add(&p2, "a");
	driver_add(&p2, "A");
	body_add(&p2, "a");
	body_add(&p2, "a");
	body_add(&p2, "A");
	body_add(&p2, "b");
	//prod_print(&p2);
	driver_add(&p3, "A");
	body_add(&p3, "#");
	//prod_print(&p3);

	grammar g;
	gram_init(&g);
	prod_add(&g, &p1);
	prod_add(&g, &p2);
	prod_add(&g, &p3);

	gram_print(&g); */


	return 0;
	}
