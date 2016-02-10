#include "libs.h"
#include "interface.h"

void rest()
{
	int continuer = 1;
	SDL_Rect position;
	SDL_Event event;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
				break;
			}
			break;
		}
	}
}

SDL_Surface *load_image(char *file_name)
{
	SDL_Surface* loadedImage = NULL, *optimizedImage = NULL;

	if (file_name == NULL)
		file_name = "image.bmp";

	if ((loadedImage = SDL_LoadBMP(file_name)) != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	SDL_Rect position;

	position.x = x;
	position.y = y;

	SDL_BlitSurface(source, NULL, destination, &position);
}