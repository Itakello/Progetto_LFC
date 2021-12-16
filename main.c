#include <stdio.h>
#include "brzozowski.h"
#include "classes/grammar.h"
#include "classes/finiteAutoma.h"
#include "classes/utility.h"

int main(int argc, char const* argv[]) {

	grammar g;
	finiteAutoma fa;

	printf("Input :\n 0 -> Grammar\n 1 -> Automa\n 2 -> Regular expression\n");
	int input;
	scanf("%d", &input);
	switch (input) {
			case 0:
				getGrammarFile(&g, "inputGrammar.txt");
				checkGrammar(&g);
				gram_print(&g);
				fa_init(&fa);
				fa_addGram(&fa, &g);
				break;
			case 1:
				getAutomaFile(&fa, "inputAutoma.txt");
				break;
			case 2:
				printf("Reg");
				break;
			default:
				perr("Wrong input", 1);
				break;
		}

	fa_print(&fa);
	/* finiteAutoma f1 = rev(&fa);
	fa_print(&f1);
	finiteAutoma f2 = det(&f1);
	fa_print(&f2); */

	return 0;
	}
