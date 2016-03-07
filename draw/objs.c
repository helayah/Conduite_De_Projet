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

	free(node);
}

root* Root_Init(int size_node, int size_way)
{
	root* node;
	int i;

	if (size_node < 0 || size_node >(size_t) - 1 / sizeof(node->arrayNode[0]))
		return NULL;

	if (size_way < 0 || size_way >(size_t) - 1 / sizeof(node->arrayWays[0]))
		return NULL;

	if ((node = malloc(sizeof(*node))) == NULL)
		return NULL;

	node->size_node = size_node;
	node->size_way = size_way;
	node->arrayNode = malloc(size_node * sizeof(*node->arrayNode[0]));

	if (node->arrayNode == NULL)
	{
		free(node);
		return NULL;
	}

	for (i = 0; i < size_node; i++)
		node->arrayNode[i] = NULL;

	node->arrayWays = malloc(size_way * sizeof(*node->arrayWays[0]));

	if (node->arrayWays == NULL)
	{
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

node_t* getNode(node_t** node, int length, uint32_t reference)
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

	for (i = 0; i < node->size_node; i++)
	{
		if (node->arrayNode[i] != NULL)
			Node_Display(node->arrayNode[i]);
	}
}

void Node_Display(node_t* node)
{
	printf("----------- Node -----------\n");
	printf("id 			= %" PRId32 "\n", node->id);
	printf("latitude 	= %lf\n", node->latitude);
	printf("longitude 	= %lf\n", node->longitude);
	printf("----------------------------\n");
}
