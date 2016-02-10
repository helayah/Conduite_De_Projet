#include "interface.h"

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Color color_white = { 0, 0, 0 };

int main(int argc, char **argv)
{
	char file_name[BUFSIZ];

	if (SDL_Init(SDL_INIT_VIDEO) == ERROR)
	{
		perror("Fail to init SDL\n");
		exit(EXIT_FAILURE);
	}
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL)
	{
		perror("NULL screen\n");
		exit(EXIT_FAILURE);
	}

	background = load_image(IMAGE_PATH);
	apply_surface(DEFAULT_X, DEFAULT_Y, background, screen);

	if (SDL_Flip(screen) == ERROR) 
	{
		exit(EXIT_FAILURE);
	}

	rest();

	SDL_FreeSurface(background);
	SDL_Quit();

	exit(EXIT_SUCCESS);
}