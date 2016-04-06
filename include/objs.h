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

#define RIVER		(WATERWAY | (1 << 0))
#define RIVERBANK	(WATERWAY | (1 << 1))

#define PARK		(LEISURE | (1 << 0))
#define GARDEN		(LEISURE | (1 << 1))

#define ANYTHING	(1 << 8)



typedef unsigned int type_t;

typedef struct bound {
	double minlat;
	double minlon;
	double maxlat;
	double maxlon;
} bound;

typedef struct way {
	uint32_t id;
	int size;
	uint32_t* ref;
	type_t type_primary;
	type_t type_secondary;
} way;

typedef struct node_t {
	uint32_t id;
	double latitude;
	double longitude;
	type_t type;
} node_t;

typedef struct Root {
	int size_nodes;
	int size_ways;
	node_t** arrayNodes;
	way** arrayWays;
} Root;

int Bound_Init(double minlat, double maxlat, double minlon, double maxlon);
int Root_Init(int sn, int sw);

node_t* Node_Init(uint32_t id, double lat, double lon);
way* Ways_Init(uint32_t id, int size);

void Bound_Display();
void Root_Display();
void Node_Display(node_t* node);
void Way_Display(way* way);
void Ref_Display(uint32_t* ref, int size);

void Root_Free();
void Objs_Free();
#endif

