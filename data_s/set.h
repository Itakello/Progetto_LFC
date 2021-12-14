#ifndef SET_H
#define SET_H

#define MAX 30
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include "..\classes\finiteAutoma.h"

void addElement(char*, const char, int*);
void removeElement(char*, const char, int*);
bool member(const char*, const char, const int);
void addTrans(transition*, const transition, int*);
void removeTrans(transition*, const transition, int*);
bool memberTrans(const transition*, const transition, const int);

#endif