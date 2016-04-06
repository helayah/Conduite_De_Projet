#include "libs.h"
#include "map.h"
#include "objs.h"
#include "trie.h"
#include "errs.h"

#define LENGTH_PATH 256

SDL_Window* pWindow = NULL;
SDL_Renderer* pRenderer = NULL;
Map* pMap = NULL;
Root* pRoot = NULL;
bound* pBound = NULL;

char DEFAULT_OSM[] = "03_paris_ile_saint_louis.osm";

int main(int argc, char** argv)
{
	char file[LENGTH_PATH];
	int i;
	
	if(argc < 1 || argc > 2)
	{
		fprintf(stdout, "%s\n", ARGC_FAILURE);
		return EXIT_FAILURE;
	}
	
	memset(file, 0, LENGTH_PATH);
	
	if(argc == 1)
		strcpy(file, DEFAULT_OSM);
	else
		strcpy(file, argv[1]);
		
	if(parse(file) == FAILURE)
	{
		Objs_Free();
		return EXIT_FAILURE;
	}
	
	if(!isSortedWays())
		tri_rapide_way(pRoot->arrayWays, pRoot->size_ways);
		
	if(Map_Init() == FAILURE)
	{
		Objs_Free();
		return EXIT_FAILURE;
	}

	for(i = 0; i < pRoot->size_ways; i++)
	{
			Draw(pRoot->arrayWays[i]);
	}

	SDL_RenderPresent(pRenderer);

	Map_Loop();
	Map_Destroy();
	Objs_Free();

	return EXIT_SUCCESS;
}

