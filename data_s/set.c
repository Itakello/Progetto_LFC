#include "set.h"

void addElement(char* set, const char el, int* dim) {
	if (!member(set, el, *dim))
		set[(*dim)++] = el;
	}

void removeElement(char* set, const char el, int* dim) {
	bool ok = false;
	for (int i = 0; i < *dim; i++) {
		if (set[i] == el)
			ok = true;
		if (ok)
			set[i] = set[i + 1];
		}
	--(*dim);
	}

bool member(const char* set, const char el, const int dim) {
	for (int i = 0; i < dim; i++) {
		if (el == set[i])
			return true;
		}
	return false;
	}

void addTrans(transition* set, const transition t, int* dim) {
	if (!memberTrans(set, t, *dim))
		set[(*dim)++] = t;
	}

void removeTrans(transition* set, const transition tc, int* dim) {
	bool ok = false;
	for (int i = 0; i < *dim; i++) {
		if (set[i].to_state == tc.to_state && set[i].from_state == tc.from_state && set[i].symbol == tc.symbol)
			ok = true;
		if (ok)
			set[i] = set[i + 1];
		}
	--(*dim);
	}

bool memberTrans(const transition* set, const transition t, const int dim) {
	for (int i = 0; i < dim; i++) {
		if (t.from_state == set[i].from_state && t.symbol == set[i].symbol && t.to_state == set[i].to_state)
			return true;
		}
	return false;
	}