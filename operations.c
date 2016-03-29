#include "operations.h"

extern SDL_Window* pWindow;
extern SDL_Renderer* pRenderer;
extern Map* pMap;
extern Root* pRoot;
extern bound* pBound;

inline int mod(int x, int div)
{
	x %= div;
	if(x < 0)
		x += div;
	return x;
}

double deg2rad(double deg)
{
	return (deg * M_PI / 180);
}

double rad2deg(double rad)
{
	return (rad * 180 / M_PI);
}

void draw(way* w)
{
	int i, indice_dans_id_noeuds = 1, compteur = 0, x, y;
	int16_t *arrayX, *arrayY;
	double lon, lat, minlat, maxlat, minlon, maxlon;
	
	
	maxlat = pBound->maxlat;
	minlat = pBound->minlat;
	maxlon = pBound->maxlon;
	minlon = pBound->minlon;

	
	arrayX = (int16_t*)malloc(w->size * sizeof(*arrayX));
	arrayY = (int16_t*)malloc(w->size * sizeof(*arrayY));
	
	for (i = 1; i < w->size + 1; i++)
	{
		if(w->ref[i] != 0)
		{
			indice_dans_id_noeuds = naive(w->ref[i]);
		
			if((indice_dans_id_noeuds >= 0)  
				&& (pRoot->arrayNodes[indice_dans_id_noeuds]->latitude >= minlat) 
				&& (pRoot->arrayNodes[indice_dans_id_noeuds]->latitude <= maxlat) 
				&& (pRoot->arrayNodes[indice_dans_id_noeuds]->longitude <= maxlon)
				&& (pRoot->arrayNodes[indice_dans_id_noeuds]->longitude >= minlon))
			{
				lon = pRoot->arrayNodes[indice_dans_id_noeuds]->longitude;
				lat = pRoot->arrayNodes[indice_dans_id_noeuds]->latitude;
			
				if(lon < minlon) 
					lon = minlon;

				if(lat > maxlat)
					lat = maxlat;
					
				x = distanceCalculation(lat, lon, lat, minlon);
				y = distanceCalculation(lat, lon, maxlat, lon);

				arrayX[compteur]=(int16_t)distanceCalculation(lat, lon, lat, minlon);
				arrayY[compteur]=(int16_t)distanceCalculation(lat, lon, maxlat, lon);
	
				compteur++;
			}
		}
	}

	switch(w->type)
	{
	case UNKNOW:

			break;
	case BUILDING:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 191, 174, 174, 100);
			polygonRGBA(pRenderer, arrayX, arrayY, compteur, 0, 0, 0, 255);
			break;
	case HIGHWAY:
			//filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 100, 100, 100, 100);
			//polygonRGBA(pRenderer, arrayX, arrayY, compteur, 0, 0, 0, 255);
			break;
	case WATERWAY:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 181, 208, 208, 255);
			break;
	case LEISURE:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 197, 240, 197, 255);
			break;
	case LANDUSE:
			break;
	case RAILWAY:
			break;
	case BRIDGE:
			break;
	default: //Should not be reached
		break;
	}
	free(arrayX);
	free(arrayY);
}

/*void draw()
{
	double minlat, maxlat, minlon, maxlon, lat, lon;
	int *arrayX, *arrayY;
	int i, j, x, y;
	uint32_t id;
	way* w = NULL;
	int compteur = 0;
	
	maxlat = pBound->maxlat;
	minlat = pBound->minlat;
	maxlon = pBound->maxlon;
	minlon = pBound->minlon;

	for (i = 0; i < pRoot->size_ways; i++)
	{
		if((w = pRoot->arrayWays[i]) != NULL)
		{
			arrayX = malloc(w->size * sizeof(*arrayX));
			arrayY = malloc(w->size * sizeof(*arrayY));
		
			for(j = 0; j < w->size; j++)
			{
				//id = search_way_dicho(w->ref[j]);
				id = naive(w->ref[j]);

				if(id != -1)
				{
					//printf("ICI\n");
					lon = pRoot->arrayNodes[id]->longitude;
					lat = pRoot->arrayNodes[id]->latitude;
				
				 	x = distanceCalculation(lat, lon, lat, minlon);
				 	y = distanceCalculation(lat, lon, maxlat, lon);
				 	
				 	printf("x = %d\ty = %d\n", x, y);
				 	free(arrayX);
					free(arrayY);
				 	return;
				 	
					arrayX[compteur] = x;
					arrayY[compteur] = y;
					
					compteur++;
				}
			}
			compteur = 0;
		
			switch(w->type)
			{
				case UNKNOW:

						break;
				case BUILDING:
						filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 191, 174, 174, 100);
						polygonRGBA(pRenderer, arrayX, arrayY, compteur, 0, 0, 0, 255);
						break;
				case HIGHWAY:
						//filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 100, 100, 100, 100);
						//polygonRGBA(pRenderer, arrayX, arrayY, compteur, 0, 0, 0, 255);
						break;
				case WATERWAY:
						filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 181, 208, 208, 255);
						break;
				case LEISURE:
						filledPolygonRGBA(pRenderer, arrayX, arrayY, compteur, 197, 240, 197, 255);
						break;
				case LANDUSE:
						break;
				case RAILWAY:
						break;
				case BRIDGE:
						break;
				default: //Should not be reached
					break;
			}
	
			free(arrayX);
			free(arrayY);
		}
		
	}
	SDL_RenderPresent(pRenderer);

}*/

int distance(double lat1, double lon1, double lat2, double lon2, int zoom)
{
	double x1, x2, y1, y2, z1, z2;

	x1 = cos(COMPUTE * lat1) * cos(COMPUTE * lon1);
	y1 = cos(COMPUTE * lat1) * sin(COMPUTE * lon1);
	
	x2 = cos(COMPUTE * lat2) * cos(COMPUTE * lon2);
	y2 = cos(COMPUTE * lat2) * sin(COMPUTE * lon2);
	
	z1 = sin(COMPUTE * lat1);
	z2 = sin(COMPUTE * lat2);
	
	return (EARTH_RADIUS * acos((x1 * x2) + (y1 * y2) + (z1 * z2))  * (1 + zoom));
}


int distanceNodes(node_t* n1, node_t* n2)
{
	double x1, x2, y1, y2, z1, z2;
	double lat1, lat2, lon1, lon2;
	
	lat1 = n1->latitude;
	lon1 = n1->longitude;
	
	lat2 = n2->latitude;
	lon2 = n2->longitude;
	
	x1 = cos(COMPUTE * lat1) * cos(COMPUTE * lon1);
	y1 = cos(COMPUTE * lat1) * sin(COMPUTE * lon1);
	
	x2 = cos(COMPUTE * lat2) * cos(COMPUTE * lon2);
	y2 = cos(COMPUTE * lat2) * sin(COMPUTE * lon2);
	
	z1 = sin(COMPUTE * lat1);
	z2 = sin(COMPUTE * lat2);
	
	return (EARTH_RADIUS * acos((x1 * x2) + (y1 * y2) + (z1 * z2)));
}
/*
int distanceCalculation(double lat1,double lon1, double lat2, double lon2, int zoom)
{
  return 
    ((int)(((rad2deg(acos((sin(deg2rad(lat1))*sin(deg2rad(lat2))) + (cos(deg2rad(lat1))*cos(deg2rad(lat2))*cos(deg2rad(lon1-lon2))))))*111133)
	   *(1 +zoom)));
}
*/

int distanceCalculation(double lat1, double lon1, double lat2, double lon2)
{
	return ((rad2deg(acos((sin(deg2rad(lat1)) * sin(deg2rad(lat2))) 
	+ (cos(deg2rad(lat1)) * cos(deg2rad(lat2))* cos(deg2rad(lon1-lon2))))))
	* 111133);
}


int naive(uint32_t id)
{
	int i;
	
	for(i = 0; i < pRoot->size_nodes; i++)
	{
		if(pRoot->arrayNodes[i] != NULL && pRoot->arrayNodes[i]->id == id)
			return i;
	}
	return FAILURE;
}

int search_way_dicho(uint32_t val)
{	
	int trouve;
	int id;
	int ifin; 
	int im; 
  
	trouve = 0;
	id = 0;
	ifin = pRoot->size_ways;
  
	while(!trouve && ((ifin - id) > 1))
	{
		im = (id + ifin)/2;
    
		trouve = (pRoot->arrayWays[im]->id == val);
    
		if(pRoot->arrayWays[im]->id > val)
			ifin = im;
		else
			id = im;
	}
  
	if(pRoot->arrayWays[id]->id == val)
		return id;
	else
		return FAILURE;
}


