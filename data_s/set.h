#ifndef SET_H
#define SET_H

#define MAX 30
#include<stdio.h>
#include<conio.h>
void create(int set[]);
void print(int set[]);
void Union(int set1[], int set2[], int set3[]);
void intersection(int set1[], int set2[], int set3[]);
void difference(int set1[], int set2[], int set3[]);
void symmdiff(int set1[], int set2[], int set3[]);
int member(int set[], int x);

#endif