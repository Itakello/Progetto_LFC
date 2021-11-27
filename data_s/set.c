#include "set.h"

void addElement(char* set, const char el, int* dim) {
	if (!member(set, el, *dim))
		set[(*dim)++] = el;
	}

bool member(const char* set, const char el, const int dim) {
	for (int i = 0; i < dim; i++) {
		if (el == set[i])
			return true;
		}
	return false;
	}