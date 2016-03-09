#include "draw.h"

extern SDL_Renderer* pRenderer;

int draw(root* node)
{
	int i = 0, j = 1, c1, c2, tmp1, tmp2;
	double coef1, coef2;
	bounds *dim;
	node_t *n1, *n2;
	
	dim = node->dimension;
	
	
	for(i = 1; i < node->size_way; i++)
	{
		/*
		n1 = node->arrayNode[i - 1];	
		coef1 = (dim->minlat - n1->latitude)/(dim->minlat - dim->maxlat);
		coef2 = (dim->minlon - n1->longitude)/(dim->minlon - dim->maxlon);
		
		tmp1 = WIDTH * coef1;
		tmp2 = HEIGHT * coef2;
		
		n1 = node->arrayNode[i];	
		coef1 = (dim->minlat - n2->latitude)/(dim->minlat - dim->maxlat);
		coef2 = (dim->minlon - n2->longitude)/(dim->minlon - dim->maxlon);
		
		c1 = WIDTH * coef1;
		c2 = HEIGHT * coef2;

		SDL_RenderDrawLine(pRenderer, 0, 0, 1, 1);
		SDL_RenderPresent(pRenderer);
		*/
		/*if(n != NULL)
		{
			coef1 = (dim->minlat - n->latitude)/(dim->minlat - dim->maxlat);
			coef2 = (dim->minlon - n->longitude)/(dim->minlon - dim->maxlon);
			c1 = WIDTH * coef1;
			c2 = HEIGHT * coef2;
			printf("%d\t%d\n", c1, c2);
			SDL_RenderDrawPoint(pRenderer, c2, c1);
			SDL_RenderPresent(pRenderer);
		}*/
	}
	
	//SDL_RenderDrawLine(pRenderer, y1, x1, y2, x2);
	//SDL_RenderPresent(pRenderer);

	return SUCCESS;
}
