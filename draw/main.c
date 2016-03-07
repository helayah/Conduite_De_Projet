#include "interface.h"
#include "objs.h"
#include "draw.h"

SDL_Window* pWindow = NULL;
SDL_Renderer* pRenderer = NULL;
root* node = NULL;
node_t** nodeArray = NULL;
ways* way = NULL;
bounds bound;

int main(int argc, char** argv)
{
	int size_node = 2, size_way = 1;

	if (SDL_VideoInit(NULL) < 0)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	bound.minlat = 48.8542200;
	bound.minlon = 2.3625300;
	bound.maxlat = 48.8569130;
	bound.maxlon = 2.3688710;

	node = Root_Init(size_node, size_way);

	node->arrayNode[0] =  Node_Init(100, 20, 20);
	node->arrayNode[1] = Node_Init(100, 21, 21);
	way = Ways_Init(1, 2);

	pWindow = SDL_CreateWindow("SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_RESIZABLE);

	if (pWindow == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	pRenderer = SDL_CreateRenderer(
		pWindow,
		DEFAULT_INDEX,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (pRenderer == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		SDL_DestroyWindow(pWindow);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 20);
	SDL_RenderPresent(pRenderer);


	draw(node, &bound);


	rest();


	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	Root_Free(node);

	exit(EXIT_SUCCESS);
}