#include <stdio.h>
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
	gram_print(&g);

	printf("\n");
	finiteAutoma fa;
	fa_init(&fa);
	fa_addGram(&fa, &g);
	fa_print(&fa);

	return 0;
	}
