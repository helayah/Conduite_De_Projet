#include "objs.h"

extern Root* pRoot;
extern bound* pBound;

int Bound_Init(double minlat, double minlon, double maxlat, double maxlon)
{
	if ((pBound = malloc(sizeof(*pBound))) == NULL)
	{
		Objs_Free();
		return FAILURE;
	}
	
	pBound->minlat = minlat;
	pBound->minlon = minlon;
	pBound->maxlat = maxlat;
	pBound->maxlon = maxlon;
	
	return SUCCESS;
}

int Root_Init(int sn, int sw)
{
	int i;
	
	if (sn < 0 || sn >(size_t) - 1 / sizeof(pRoot->arrayNodes[0]))
		return FAILURE;

	if (sw < 0 || sw >(size_t) - 1 / sizeof(pRoot->arrayWays[0]))
		return FAILURE;
		
	if ((pRoot = malloc(sizeof(*pRoot))) == NULL)
	{
		free(pBound);
		return FAILURE;
	}
	
	pRoot->size_nodes = sn;
	pRoot->size_ways = sw;
	pRoot->arrayNodes = malloc(pRoot->size_nodes * sizeof(*pRoot->arrayNodes[0]));

	if (pRoot->arrayNodes == NULL)
	{
		Objs_Free();
		return FAILURE;
	}

	for (i = 0; i < pRoot->size_nodes; i++)
		pRoot->arrayNodes[i] = NULL;

	pRoot->arrayWays = malloc(pRoot->size_ways * sizeof(*pRoot->arrayWays[0]));

	if (pRoot->arrayWays == NULL)
	{
		Objs_Free();
		return FAILURE;
	}

	for (i = 0; i < pRoot->size_ways; i++)
		pRoot->arrayWays[i] = NULL;
	
	return SUCCESS;
}

node_t* Node_Init(uint32_t id, double lat, double lon)
{
	node_t* node = NULL;

	if ((node = malloc(sizeof(*node))) == NULL)
		return NULL;

	node->id = id;
	node->latitude = lat;
	node->longitude = lon;

	return node;
}

way* Ways_Init(uint32_t id, int size)
{
	way* w = NULL;
	int i;

	if (size < 0 || size >(size_t) - 1 / sizeof(w->ref))
		return NULL;

	if ((w = malloc(sizeof(*w))) == NULL)
		return NULL;

	w->id = id;
	w->size = size;
	w->type = UNKNOW;
	w->ref = malloc(size * sizeof(*w->ref));

	if (w->ref == NULL)
	{
		free(w);
		return NULL;
	}

	for (i = 0; i < size; i++)
		w->ref[i] = 0;

	return w;
}

/*int Root_Add(node_t n, int index)
{
	if(n == NULL)
		return FAILURE;


}*/

void Bound_Display()
{
	printf("----------- Bounds -----------\n");
	printf("minlat	= %6.7f\n", pBound->minlat);
	printf("minlon	= %6.7f\n", pBound->minlon);
	printf("maxlat	= %6.7f\n", pBound->maxlat);
	printf("maxlon 	= %6.7f\n", pBound->maxlon);
	printf("------------------------------\n");
}

void Root_Display()
{
	int i;

	printf("size_nodes = %d\n", pRoot->size_nodes);
	printf("size_ways = %d\n", pRoot->size_ways);
	for (i = 0; i < pRoot->size_nodes; i++)
	{
		if(i == 20)
			break;
		/*if (pRoot->arrayNodes[i] != NULL)
			Node_Display(pRoot->arrayNodes[i]);*/
			
		if (pRoot->arrayWays[i] != NULL)
			Way_Display(pRoot->arrayWays[i]);

	}
}

void Node_Display(node_t* node)
{
	printf("------------- Node -------------\n");
	printf("id 		= %" PRId32 "\n", node->id);
	printf("latitude 	= %6.7f\n", node->latitude);
	printf("longitude 	= %6.7f\n", node->longitude);
	printf("--------------------------------\n");
}

void Way_Display(way* w)
{
	printf("------------- Way -------------\n");
	printf("id 	= %" PRId32 "\n", w->id);
	printf("size_ref = %d\n", w->size);
	printf("type 	= %d\n", w->type);
	Ref_Display(w->ref, w->size);
	printf("-------------------------------\n");
}

void Ref_Display(uint32_t* ref, int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		if(ref[i] != 0)
			printf("ref	= %" PRId32 "\n", ref[i]);
	}
}

void Root_Free()
{
	int i;

	if (pRoot->arrayNodes != NULL)
	{
		for (i = 0; i < pRoot->size_nodes; i++)
		{
			if (pRoot->arrayNodes[i] != NULL)
				free(pRoot->arrayNodes[i]);
		}
		free(pRoot->arrayNodes);
	}

	if (pRoot->arrayWays != NULL)
	{
		for (i = 0; i < pRoot->size_ways; i++)
		{
			if (pRoot->arrayWays[i] != NULL)
			{
				free(pRoot->arrayWays[i]);
			}

		}
		free(pRoot->arrayWays);
	}

	free(pRoot);
}

void Objs_Free()
{
	if(pRoot != NULL)
		Root_Free();
	if(pBound != NULL)
		free(pBound);
}
