#ifndef MAP_INCLUDED_H
#define MAP_INCLUDED_H

#include "libs.h"
#include "operations.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define WINDOW_W		800
#define WINDOW_H		800
#define DELAY_TIME 		5000
#define DEFAULT_INDEX 	-1

#define TILESIZE 		256

#define ZOOM_MAX 		10
#define ZOOM_MIN 		0

typedef struct Map {
	int width;
	int height;
	int offsetx;
	int offsety;
	int zoom;
} Map;

int Map_Init();
void Map_ZoomIn();
void Map_ZoomOut();
void Map_Destroy();

#endif

