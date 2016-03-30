#ifndef TRIE_INCLUDED_H
#define TRIE_INCLUDED_H

#include "libs.h"
#include "objs.h"

void echanger_way(way **t, int i, int j);
int partition_way(way **t, int deb, int fin);
void tri_rapide_bis_way(way **t, int debut, int fin);
void tri_rapide_way(way **t, int n);

int isSortedNodes();
int isSortedWays();


#endif

