#include "operation.h"

extern SDL_Renderer* pRenderer;
extern root* Root;

//Aide collegue calcul.
double deg2rad(double deg)
{
	return (deg * PI / 180);
}
double rad2deg(double rad)
{
	return (rad * 180 / PI);
}

int distanceCalculation(double lat1, double lon1, double lat2, double lon2)
{
	return ((rad2deg(acos((sin(deg2rad(lat1)) * sin(deg2rad(lat2))) 
	+ (cos(deg2rad(lat1)) * cos(deg2rad(lat2))* cos(deg2rad(lon1-lon2))))))
	* 111133);
}

//TODO : Aucun parametre
void draw(ways* way)
{
	int i, index = 1, compt = 0;
	int16_t *arrayX, *arrayY;
	double lon, lat;
	
	arrayX = (int16_t*)malloc(way->size * sizeof(*arrayX));
	arrayY = (int16_t*)malloc(way->size * sizeof(*arrayY));
	
	for (i = 1; i < way->size + 1; i++)
	{
		if(way->ref[i] != 0)
		{
			index = naive(way->ref[i]);
		
			if((index >= 0)  
				&& (Root->arrayNode[index]->latitude >= Root->dimension->minlat) 
				&& (Root->arrayNode[index]->latitude <= Root->dimension->maxlat) 
				&& (Root->arrayNode[index]->longitude <= Root->dimension->maxlon)
				&& (Root->arrayNode[index]->longitude >= Root->dimension->minlon))
			{
				lon = Root->arrayNode[index]->longitude;
				lat = Root->arrayNode[index]->latitude;
			
				if(lon < Root->dimension->minlon) 
					lon = Root->dimension->minlon;

				if(lat > Root->dimension->maxlat)
					lat = Root->dimension->maxlat;

				arrayX[compt]=(int16_t)distanceCalculation(lat, lon, lat, Root->dimension->minlon);
				arrayY[compt]=(int16_t)distanceCalculation(lat, lon, Root->dimension->maxlat, lon);
	
				compt++;
			}
		}
	}

	switch(way->type)
	{
	case UNKNOW:

			break;
	case BUILDING:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compt, 191, 174, 174, 100);
			polygonRGBA(pRenderer, arrayX, arrayY, compt, 0, 0, 0, 255);
			break;
	case HIGHWAY:
			//filledPolygonRGBA(pRenderer, arrayX, arrayY, compt, 100, 100, 100, 100);
			//polygonRGBA(pRenderer, arrayX, arrayY, compt, 0, 0, 0, 255);
			break;
	case WATERWAY:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compt, 181, 208, 208, 255);
			break;
	case LEISURE:
			filledPolygonRGBA(pRenderer, arrayX, arrayY, compt, 197, 240, 197, 255);
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

void echanger(uint32_t *t, int i, int j)
{
	uint32_t tmp;
	tmp = t[i];
	t[i] = t[j];
	t[j] = tmp;
}

int partition(uint32_t *t, int deb, int fin)
{
	int compt = deb;
	uint32_t pivot = t[deb];
	int i;
	
	for (i = deb+1; i <= fin; i++)
	{
		if(t[i] < pivot)
		{
			compt++;
			echanger(t, compt, i);
		}
	}
	echanger(t, compt, deb); 
	return compt;
}

void tri_rapide_bis(uint32_t *t, int debut, int fin)
{ 
	if(debut < fin)
	{
		int pivot = partition(t, debut, fin);
		tri_rapide_bis(t, debut, pivot-1);
		tri_rapide_bis(t, pivot+1, fin);
	}
}

void tri_rapide(uint32_t *t, int n)
{
	tri_rapide_bis(t, 0, n-1);
}

int naive(uint32_t id)
{
	int i;
	
	for(i = 0; i < Root->size_node; i++)
	{
		if(Root->arrayNode[i] != NULL && Root->arrayNode[i]->id == id)
			return i;
	}
	return FAILURE;
}

int dichotomie(uint32_t id_a_trouver)
{
	int trouve, id, ifin, im;
  
  	trouve = 0;
  	id = 0;
  	ifin = Root->size_node;
  

	while(!trouve && ((ifin - id) > 1))
	{
		im = (id + ifin) / 2;  
		trouve = (Root->arrayNode[im]->id == id_a_trouver);
    
    	if(Root->arrayNode[im]->id > id_a_trouver) 
    		ifin = im;  
    	else 
    		id = im;
	}

	if(Root->arrayNode[id]->id == id_a_trouver)
		return id;
	else
		return FAILURE;
}





