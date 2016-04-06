#ifndef OPERATIONS_INCLUDED_H
#define OPERATIONS_INCLUDED_H

#include "libs.h"
#include "objs.h"
#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define EARTH_RADIUS 6378137
#define COMPUTE (M_PI / 180)

void draw(way* w);
int distance(double lat1, double lon1, double lat2, double lon2);
int naive(uint32_t id);
int search_way_dicho(uint32_t val);

void Draw(way* w);
void Draw_BUILDING(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_HIGHWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_WATERWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_LEISURE(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_LANDUSE(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_RAILWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type);
void Draw_BRIDGE(Sint16 *vx, Sint16 *vy, int coord, type_t type);

#endif

