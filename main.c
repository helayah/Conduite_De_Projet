#include "interface.h"
#include "parser.h"
#include "objs.h"
<<<<<<< HEAD
#include "operation.h"
=======
#include "draw.h"
>>>>>>> origin/master

#define EXT_OSM_LENGTH 4

SDL_Window* pWindow = NULL;
SDL_Renderer* pRenderer = NULL;
root* Root = NULL;
<<<<<<< HEAD

int is_mtrFile(char *file_name);

int main(int argc, char** argv)
{
	int i, lat, lon, coef = 1;
	
	if(argc <= 1 || argc > 2)
	{
		fprintf(stdout, "%s\n", NUMBER_ARGUMENT_FAILURE);
		return EXIT_FAILURE;
	}
	
	if(!is_mtrFile(argv[1]))
	{
		fprintf(stdout, "%s\n", NOT_AN_OS_FILE);
		return EXIT_FAILURE;
	}

	if(parse(argv[1]) == FAILURE)
	{
		fprintf(stdout, "%s\n", PARSING_FAILURE);
		return EXIT_FAILURE;
	}
=======

int is_mtrFile(char *file_name);

int main(int argc, char** argv)
{
	if(argc <= 1 || argc > 2)
	{
		fprintf(stdout, "%s\n", NUMBER_ARGUMENT_FAILURE);
		exit(EXIT_FAILURE);
	}
	
	if(!is_mtrFile(argv[1]))
	{
		fprintf(stdout, "%s\n", NOT_AN_OS_FILE);
		exit(EXIT_FAILURE);
	}

	if((Root = parse(argv[1])) == NULL)
	{
		fprintf(stdout, "%s\n", PARSING_FAILURE);
		exit(EXIT_FAILURE);
	}


	if(Root != NULL)
	{
	
		if (SDL_VideoInit(NULL) < 0)
		{
			fprintf(stdout, "%s\n", SDL_GetError());
			Root_Free(Root);
			exit(EXIT_FAILURE);
		}
	
		pWindow = SDL_CreateWindow("SDL",

		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_RESIZABLE);


		if (pWindow == NULL)
		{
			fprintf(stdout, "%s\n", SDL_GetError());
			Root_Free(Root);
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
			Root_Free(Root);
			SDL_DestroyWindow(pWindow);
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);


		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 20);
		SDL_RenderPresent(pRenderer);

		draw(Root);
		
		rest();
	
		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(pWindow);
		SDL_Quit();

		Root_Free(Root);	
	}
	
	/*int size_node = 2, size_way = 1;

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
>>>>>>> origin/master

	lat = distanceCalculation(Root->dimension->maxlat, Root->dimension->maxlon, Root->dimension->minlat, Root->dimension->maxlon);  
  	lon = distanceCalculation(Root->dimension->minlat, Root->dimension->minlon, Root->dimension->minlat, Root->dimension->maxlon); 
		
	while(lon > 1000 || lat > 1000)
	{
		coef = coef * 2;
		lon = lon / coef;
		lat = lat / coef;
	}
		
	
	if (SDL_VideoInit(NULL) < 0)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		Root_Free(Root);
		return EXIT_FAILURE;
	}
	
	pWindow = SDL_CreateWindow("SDL",
<<<<<<< HEAD
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	lon,
	lat,
	SDL_WINDOW_RESIZABLE);
=======
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_RESIZABLE);
>>>>>>> origin/master

	if (pWindow == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
<<<<<<< HEAD
		Root_Free(Root);
		return EXIT_FAILURE;
	}
	
	pRenderer = SDL_CreateRenderer(
		pWindow,
		DEFAULT_INDEX,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

=======
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	pRenderer = SDL_CreateRenderer(
		pWindow,
		DEFAULT_INDEX,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
>>>>>>> origin/master

	if (pRenderer == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
<<<<<<< HEAD
		Root_Free(Root);
		return EXIT_FAILURE;
	}
	
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	SDL_RenderPresent(pRenderer); 
	
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(pRenderer);
	
	//TODO : Aucun for
	for(i = 0; i < Root->size_way - 1; i++)
	{
		draw(Root->arrayWays[i]);
	}
	
	SDL_RenderPresent(pRenderer);
	//SDL_Delay(DELAY_TIME);
=======
		SDL_DestroyWindow(pWindow);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);

	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 20);
	SDL_RenderPresent(pRenderer);


	draw(node, &bound);


>>>>>>> origin/master
	rest();
	
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

<<<<<<< HEAD
	Root_Free(Root);
	
	return EXIT_SUCCESS;
=======

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	Root_Free(node);*/

	exit(EXIT_SUCCESS);
>>>>>>> origin/master
}

int is_mtrFile(char *file_name)
{
	int size = (int)(strlen(file_name) >= 5) ? strlen(file_name) - EXT_OSM_LENGTH : 0;

	if (!strncmp(".osm", &file_name[size], EXT_OSM_LENGTH))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
