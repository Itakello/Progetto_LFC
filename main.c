#include <stdio.h>
#include "classes/utility.h"
#include "classes/grammar.h"

int main(int argc, char const* argv[]) {
	grammar g;
	if (!getGrammarFile(&g, "input.txt")) {
		getGrammarCin(&g);
		}
	gram_print(&g);

	return 0;
	}
