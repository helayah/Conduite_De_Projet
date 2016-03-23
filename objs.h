#ifndef OBJS_INCLUDED_H
#define OBJS_INCLUDED_H

#include "libs.h"

#define UNKNOW 		-1
#define BUILDING 	(1 << 0)
#define HIGHWAY 	(1 << 1)
#define WATERWAY 	(1 << 2)
#define LEISURE 	(1 << 4)
#define LANDUSE 	(1 << 5)
#define RAILWAY 	(1 << 6)
#define BRIDGE 		(1 << 7)

typedef unsigned int type_t;

typedef struct position {
	float latitude;
	float longitude;
} position;

typedef struct user {
	char* name;
	uint16_t id;
} user;

typedef struct ways {
	uint32_t id;
	int size;
	uint32_t* ref;
	type_t type;
} ways;

typedef struct bounds {
	double minlat;
	double minlon;
	double maxlat;
	double maxlon;
} bounds;

typedef struct node_t {
	uint32_t id;
	double latitude;
	double longitude;
	/*position* pos;
	struct user puser;
	int visible;
	unsigned short version;
	uint32_t changeset;
	time_t timestamp;*/
} node_t;

typedef struct root {
	int size_node;
	int size_way;
	bounds* dimension;
	node_t** arrayNode;
	ways** arrayWays;
} root;

void Root_Free(root* node);
root* Root_AddNode(root* r, node_t* node);
root* Root_AddWay(root* r, ways* way);
root* Root_Init(int size_node, int size_way, bounds* b);
node_t* Node_Init(uint32_t id, double lat, double lon);
ways* Ways_Init(uint32_t id, int size);
node_t* Root_GetNode(root* node, int length, uint32_t reference);

void Root_Display(root* node);
void Way_Display(ways* way);
void Ref_Display(uint32_t* ref, int size);
void Node_Display(node_t* node);
void Bound_Display(bounds* b);
#endif
