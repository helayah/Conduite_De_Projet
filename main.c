#include "interface.h"
//#include "parser.h"

SDL_Window* pWindow = NULL;
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
	
	SDL_Init(SDL_INIT_VIDEO);

	pWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (pWindow == NULL)
	{
		fprintf(stdout, "%s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
	}
    rest();

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

