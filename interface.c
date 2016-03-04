#include "libs.h"
#include "interface.h"

void rest()
{
	SDL_Event event;

	while (1)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			return;
		}
	}
}
