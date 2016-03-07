#include "draw.h"

extern SDL_Renderer* pRenderer;

int draw(root* node, bounds* bound)
{
	int x1, x2, y1, y2;

	x1 = 10;
	x2 = 20;

	y1 = 300;
	y2 = 400;

	SDL_RenderDrawLine(pRenderer, y1, x1, y2, x2);
	SDL_RenderPresent(pRenderer);

	return SUCCESS;
}
