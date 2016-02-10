#ifndef INTERFACE_INCLUDED_H
#define INTERFACE_INCLUDED_H

#include "libs.h"
#include <SDL.h>

#define ERROR -1
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 800
#define SCREEN_BPP 32
#define DEFAULT_X 0
#define DEFAULT_Y 0

#define IMAGE_PATH "image.bmp"

void rest();
SDL_Surface *load_image(char *file_name);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif
