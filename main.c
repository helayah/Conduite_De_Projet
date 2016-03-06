#include "interface.h"
#include "objs.h"
//#include "parser.h"

SDL_Window* pWindow = NULL;
SDL_Renderer* pRenderer = NULL;
node_t* array = NULL;
//SDL_Surface *screen = NULL;

//GCC : gcc -Wall main.c interface.c -I./usr/x86_64-w64-mingw32/sys-root/mingw/include/SDL2 -L./usr/x86_64-w64-mingw32/sys-root/mingw/lib
//GCC : gcc -Wall main.c parser.c -I/usr/include/libxml2 -lxml2 -o main
int main(int argc, char **argv)
{
	/*char* file;

	file = "01_denver_lafayette.osm";
	
	if (parse(file) == FAILURE)
	{
		fprintf(stderr, "%s\n", PARSING_FAILURE);
		exit(EXIT_FAILURE);
	}*/
	array = malloc(sizeof(struct node_t *) * 2);
    array[0]->id = 1;
    array[0]->pos.longitute = 20.0;
    array[0]->pos.latitude = 20.0;
    
    array[1]->id = 2;
    array[1]->pos.longitute = 21.0;
    array[1]->pos.latitude = 21.0;
    
    
	SDL_Init(SDL_INIT_VIDEO);

	pWindow = SDL_CreateWindow("SDL",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_SHOWN);

	if (pWindow == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
        free(array);
        SDL_Quit();
        exit(EXIT_FAILURE);
	}
    
    rest();
    free(array);
    SDL_DestroyWindow(pWindow);
	SDL_Quit();
	
    
    /*SDL_Init(SDL_INIT_EVERYTHING);

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	

	if (screen == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	rest();

	SDL_FreeSurface(screen);
	SDL_Quit();*/
    
    
	exit(EXIT_SUCCESS);
}

