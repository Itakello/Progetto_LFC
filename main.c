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
				if (!getGrammarFile(&g, "inputGrammar.txt"))
					getGrammarCin(&g);
				checkGrammar(&g);
				gram_print(&g);
				fa_init(&fa);
				fa_addGram(&fa, &g);
				fa_print(&fa);
				break;
			case 1:
				if (!getAutomaFile(&fa, "inputAutoma.txt"))
					getAutomaCin(&fa);
				fa_print(&fa);
				break;
			case 2:
				printf("Reg");
				break;
			default:
				perr("Wrong input", 1);
				break;
		}

	finiteAutoma f1 = rev(&fa);
	fa_print(&f1);
	//det(&f1);

	return 0;
	}
