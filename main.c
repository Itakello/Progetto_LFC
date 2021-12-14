#include <stdio.h>
#include "brzozowski.h"
#include "classes/utility.h"
#include "classes/grammar.h"
#include "classes/finiteAutoma.h"

int main(int argc, char const* argv[]) {
	printf("Start\n");
	grammar g;
	if (!getGrammarFile(&g, "input.txt")) {
		getGrammarCin(&g);
		}
	checkGrammar(&g);
	//gram_print(&g);

	printf("\n");
	finiteAutoma fa;
	fa_init(&fa);
	fa_addGram(&fa, &g);
	fa_print(&fa);
	printf("\n");
	finiteAutoma f1 = rev(&fa);
	fa_print(&f1);

	return 0;
	}
