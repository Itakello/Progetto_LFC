#ifndef PRODUCTION_H
#define PRODUCTION_H

typedef struct production {
	char driver; //Deve contenere un simbolo non-terminale
	char body[2];
	int tot_body;
	} production;

void set_driver(production*, char);
void body_add(production*, const char*);
void prod_print(production*);
void body_delete(production*);

#endif