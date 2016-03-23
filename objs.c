#include "objs.h"

void Root_Free(root* node)
{
	int i;

	if (node->arrayNode != NULL)
	{
		for (i = 0; i < node->size_node; i++)
		{
			if (node->arrayNode[i] != NULL)
				free(node->arrayNode[i]);
		}
		free(node->arrayNode);
	}

	if (node->arrayWays != NULL)
	{
		for (i = 0; i < node->size_way; i++)
		{
			if (node->arrayWays[i] != NULL)
			{
				free(node->arrayWays[i]);
			}

		}
		free(node->arrayWays);
	}

	free(node->dimension);
	free(node);
}

root* Root_AddNode(root* r, node_t* node)
{
	int i;
	
	for(i = 0; i < r->size_node; i++)
	{
		if(r->arrayNode[i] == NULL)
			r->arrayNode[i] = node;	
	}
	
	return r;
}

root* Root_AddWay(root* r, ways* way)
{
	int i;
	
	for(i = 0; i < r->size_way; i++)
	{
		if(r->arrayWays[i] == NULL)
			r->arrayWays[i] = way;	
	}
	
	return r;
}

root* Root_Init(int size_node, int size_way, bounds* b)
{
	root* node;
	int i;
	
	if (size_node < 0 || size_node >(size_t) - 1 / sizeof(node->arrayNode[0]))
		return NULL;

	if (size_way < 0 || size_way >(size_t) - 1 / sizeof(node->arrayWays[0]))
		return NULL;
	
	if(b == NULL)
		return NULL;

	if ((node = malloc(sizeof(*node))) == NULL)
		return NULL;
		
	if ((node->dimension = malloc(sizeof(*node->dimension))) == NULL)
	{
		free(node);
		return NULL;
	}

	node->size_node = size_node;
	node->size_way = size_way;
	node->dimension->minlat = b->minlat;
	node->dimension->maxlat = b->maxlat;
	node->dimension->minlon = b->minlon;
	node->dimension->maxlon = b->maxlon;
	
	node->arrayNode = malloc(size_node * sizeof(*node->arrayNode[0]));

	if (node->arrayNode == NULL)
	{
		free(node->dimension);
		free(node);
		return NULL;
	}

	for (i = 0; i < size_node; i++)
		node->arrayNode[i] = NULL;

	node->arrayWays = malloc(size_way * sizeof(*node->arrayWays[0]));

	if (node->arrayWays == NULL)
	{
		free(node->dimension);
		free(node->arrayNode);
		free(node);
		return NULL;
	}

	for (i = 0; i < size_way; i++)
		node->arrayWays[i] = NULL;

	return node;
}

ways* Ways_Init(uint32_t id, int size)
{
	ways* way;
	int i;

	if (size < 0 || size >(size_t) - 1 / sizeof(way->ref))
		return NULL;

	if ((way = malloc(sizeof(*way))) == NULL)
		return NULL;

	way->id = id;
	way->size = size;
	way->type = UNKNOW;
	way->ref = malloc(size * sizeof(*way->ref));

	if (way->ref == NULL)
	{
		free(way);
		return NULL;
	}

	for (i = 0; i < size; i++)
		way->ref[i] = 0;

	return way;
}

node_t* Node_Init(uint32_t id, double lat, double lon)
{
	node_t* node;

	if ((node = malloc(sizeof(*node))) == NULL)
		return NULL;

	node->id = id;
	node->latitude = lat;
	node->longitude = lon;

	return node;
}

node_t* Root_GetNode(root* node, int length, uint32_t reference)
{
	int i;

	for (i = 0; i < length; i++)
	{
	}

	return NULL;
}


void Root_Display(root* node)
{
	int i;

	//printf("size_node = %d\n", node->size_node);
	//printf("size_way = %d\n", node->size_way);
	for (i = 0; i < node->size_node; i++)
	{
		if (node->arrayNode[i] != NULL)
			Node_Display(node->arrayNode[i]);
			
		/*if (node->arrayWays[i] != NULL)
			Way_Display(node->arrayWays[i]);*/

	}
}

void Way_Display(ways* way)
{
	printf("------------- Way -------------\n");
	printf("id 	= %" PRId32 "\n", way->id);
	printf("size 	= %d\n", way->size);
	printf("type 	= %d\n", way->type);
	Ref_Display(way->ref, way->size);
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

void Node_Display(node_t* node)
{
	printf("------------- Node -------------\n");
	printf("id 		= %" PRId32 "\n", node->id);
	printf("latitude 	= %6.7f\n", node->latitude);
	printf("longitude 	= %6.7f\n", node->longitude);
	printf("--------------------------------\n");
}

void Bound_Display(bounds* b)
{
	printf("----------- Bounds -----------\n");
	printf("minlat	= %6.7f\n", b->minlat);
	printf("minlon	= %6.7f\n", b->minlon);
	printf("maxlat	= %6.7f\n", b->maxlat);
	printf("maxlon 	= %6.7f\n", b->maxlon);
	printf("------------------------------\n");
}
