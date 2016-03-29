#ifndef MAP_INCLUDED_H
#define MAP_INCLUDED_H

#include "libs.h"
#include "operations.h"
#include <SDL2/SDL.h>

#define WINDOW_W		800
#define WINDOW_H		800
#define DELAY_TIME 		5000
#define DEFAULT_INDEX 	-1

#define TILESIZE 		256

typedef struct Map {
	int width;
	int height;
	int offsetx;
	int offsety;
	int zoom;
} Map;

int Map_Init();
void Map_Center(double lat, double lon);
void Map_Render();
void Map_Resize(int w, int h);
void Map_UpdateBounds();
void Map_Destroy();

#endif
