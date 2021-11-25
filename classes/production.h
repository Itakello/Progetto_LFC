#ifndef PRODUCTION_H
#define PRODUCTION_H
#define DRIVER_CAP 30
#define BODY_CAP 30

typedef struct production {
	char driver[DRIVER_CAP]; //Deve contenere almeno un simbolo non-terminale
	int tot_driver;
	char body[BODY_CAP];
	int tot_body;
	} production;

void prod_init(production*);
void driver_add(production*, char);
void body_add(production*, char);
void prod_print(production*);
void prod_delete(production*);

#endif