#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "..\data_s\vector.h"

typedef struct production {
	vector driver; //Deve contenere almeno un simbolo non-terminale
	vector body;
	} production;

void prod_init(production*);
void driver_add(production*, char*);
void body_add(production*, char*);
void prod_print(production*);
void prod_delete(production*);

#endif