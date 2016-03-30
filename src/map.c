#include "map.h"

extern SDL_Window* pWindow;
extern SDL_Renderer* pRenderer;
extern Map* pMap;
extern Root* pRoot;
extern bound* pBound;

int Map_Init()
{
	if (SDL_VideoInit(NULL) < 0)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		return FAILURE;
	}
	
	if ((pMap = malloc(sizeof(*pMap))) == NULL)
	{
		fprintf(stdout, "%s\n", strerror(errno));
		Map_Destroy();
		return FAILURE;
	}
	
	pMap->width = WINDOW_W;
	pMap->height = WINDOW_H;
	pMap->offsetx = 0;
	pMap->offsety = 0;
	pMap->zoom = 0;
	
	pWindow = SDL_CreateWindow("MAP",
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	WINDOW_W,
	WINDOW_H,
	SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (pWindow == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		Map_Destroy();
		return FAILURE;
	}
	
	pRenderer = SDL_CreateRenderer(
		pWindow,
		DEFAULT_INDEX,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (pRenderer == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		Map_Destroy();
		return FAILURE;
	}
	
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	SDL_RenderPresent(pRenderer); 
	
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(pRenderer);
		
	return SUCCESS;
}

void Map_Loop()
{
	SDL_Event event;
	//bool mousedown = false;
	int i, zoomdf = 0;
	bool dirty = false;

	for(;;)
	{
		SDL_WaitEvent(&event);
		
		switch (event.type)
		{
			case SDL_MOUSEBUTTONUP://TODO:non minimal
				//mousedown = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return;
					case SDLK_PLUS:
					case SDLK_EQUALS:
						/*Map_ZoomIn();
						dirty = true;*/
						break;
					case SDLK_MINUS:
						/*Map_ZoomOut();
						dirty = true;*/
						break;
				}
			case SDL_MOUSEWHEEL://TODO:non minimal
				zoomdf += event.wheel.y;
				if(zoomdf >= 5)
				{
					zoomdf = 0;
					Map_ZoomIn();
					dirty = true;
				}
				else
					if(zoomdf <= -5)
					{
						zoomdf = 0;
						Map_ZoomOut();
						dirty = true;
					}
				break;
			case SDL_MOUSEMOTION: //TODO:non minimal
				break;
			case SDL_WINDOWEVENT:
					switch(event.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							//Map_Resize(event.window.data1, event.window.data2);
							/*dirty = true;
							Map_ZoomIn();*/
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							/*dirty = true;
							Map_ZoomOut();*/
							break;
					}
					break;
			case SDL_QUIT:
				return;
		}
		
		if(dirty)
		{
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderClear(pRenderer);
			SDL_RenderPresent(pRenderer); 
			for(i = 0; i < pRoot->size_ways; i++)
			{
				draw(pRoot->arrayWays[i], pMap->zoom);
			}
			SDL_RenderPresent(pRenderer);
			dirty = false;
		}

	}
}

void Map_Center(double lat, double lon)
{
	double x, y;
	
	x = (lon + 180.0f) / 360.0f;
	y = (1.0f - log(tan(lat * M_PI / 180.0f) + 1.0f / cos(lat * M_PI / 180.0f)) / M_PI) / 2.0f;
	pMap->offsetx = x * (TILESIZE << pMap->zoom) - pMap->width / 2;
	pMap->offsety = y * (TILESIZE << pMap->zoom) - pMap->height / 2;
}

void Map_ZoomIn()
{
	if(pMap->zoom == ZOOM_MAX)
		return;
		
	pMap->zoom++;
}

void Map_ZoomOut()
{
	if(pMap->zoom == ZOOM_MIN)
		return;
		
	pMap->zoom--;
}

void Map_Render()
{
	SDL_UpdateWindowSurface(pWindow);
}

void Map_Resize(int w, int h)
{
	pMap->offsetx += (pMap->width - w) / 2;
	pMap->offsety += (pMap->height - h) / 2;

	pMap->width = w;
	pMap->height = h;
}

void Map_UpdateBounds()
{
	int maxy = (1 << pMap->zoom) * TILESIZE - pMap->height;
	if(pMap->offsety < 0)
		pMap->offsety = 0;
	else if(pMap->offsety > maxy)
		pMap->offsety = maxy;

	pMap->offsetx = mod(pMap->offsetx, TILESIZE * (1 << pMap->zoom));
}

void Map_Destroy()
{
	if(pMap != NULL)
		free(pMap);
	if(pRenderer != NULL)
		SDL_DestroyRenderer(pRenderer);
	if(pWindow != NULL)
		SDL_DestroyWindow(pWindow);
	SDL_Quit();
}
