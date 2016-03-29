#ifndef OPERATIONS_INCLUDED_H
#define OPERATIONS_INCLUDED_H

#include "libs.h"
#include "objs.h"
#include "map.h"

//#define EARTH_RADIUS 6371 //km
#define EARTH_RADIUS 6378137
#define COMPUTE (M_PI / 180)

inline int mod(int x, int div);
double deg2rad(double deg);
double rad2deg(double rad);

void draw(way* w);

int distance(double lat1, double lon1, double lat2, double lon2, int zoom);
int distanceNodes(node_t* n1, node_t* n2);
int distanceCalculation(double lat1, double lon1, double lat2, double lon2);

int naive(uint32_t id);
int search_way_dicho(uint32_t val);

#endif

