#include "trie.h"

extern Root* pRoot;

void echanger_way(way **t, int i, int j)
{
	way* tmp;
	tmp = t[i];
	t[i] = t[j];
	t[j] = tmp;
}

int partition_way(way **t, int deb, int fin)
{
	int compt = deb;
	uint32_t pivot = t[deb]->id;
	int i;
	
	for (i = deb+1; i <= fin; i++)
	{
		if(t[i]->id < pivot)
		{
			compt++;
			echanger_way(t, compt, i);
		}
	}
	echanger_way(t, compt, deb); 
	return compt;
}

void tri_rapide_bis_way(way **t, int debut, int fin)
{ 
	if(debut < fin)
	{
		int pivot = partition_way(t, debut, fin);
		tri_rapide_bis_way(t, debut, pivot-1);
		tri_rapide_bis_way(t, pivot+1, fin);
	}
}

void tri_rapide_way(way **t, int n)
{
	tri_rapide_bis_way(t, 0, n-1);
}

int isSortedNodes()
{
	int i;

	for(i = 0; i < pRoot->size_nodes - 1; i++)
	{
		if(pRoot->arrayNodes[i]->id > pRoot->arrayNodes[i + 1]->id)
			return 0;
	}

	return 1;
}

int isSortedWays()
{
	int i;

	for(i = 0; i < pRoot->size_ways - 1; i++)
	{
		if(pRoot->arrayWays[i]->id > pRoot->arrayWays[i + 1]->id)
			return 0;
	}

	return 1;
}
