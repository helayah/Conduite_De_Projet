//#include "interface.h"
#include "parser.h"
/*
SDL_Window* pWindow = NULL;
*/


//GCC : gcc -Wall main.c parser.c -I/usr/include/libxml2 -lxml2 -o main
int main(int argc, char **argv)
{
	char* file;

	file = "01_denver_lafayette.osm";
	
	if (parse(file) == FAILURE)
	{
		fprintf(stderr, "%s\n", PARSING_FAILURE);
		exit(EXIT_FAILURE);
	}
	
	/*
	SDL_Init(SDL_INIT_VIDEO);

	pWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (pWindow != NULL)
	{
		rest();
	}
	else
	{
		perror("SDL_CreateWindow !\n");
	}

	SDL_Quit();

	return EXIT_SUCCESS;*/
	
	exit(EXIT_SUCCESS);
}

