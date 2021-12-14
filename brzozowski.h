#ifndef BRZOZOWSKI_H
#define BRZOZOWSKI_H

#include "classes/finiteAutoma.h"
#include "classes\utility.h"

void dfs(const finiteAutoma* fa, bool* visited, int u);
finiteAutoma rev(const finiteAutoma*);
finiteAutoma det(const finiteAutoma*);
finiteAutoma brzozowki(const finiteAutoma*);

#endif