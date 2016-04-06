#include "operations.h"

extern SDL_Window* pWindow;
extern SDL_Renderer* pRenderer;
extern Map* pMap;
extern Root* pRoot;
extern bound* pBound;


int distance(double lat1, double lon1, double lat2, double lon2)
{
	double x1, x2, y1, y2, z1, z2;

	x1 = cos(COMPUTE * lat1) * cos(COMPUTE * lon1);
	y1 = cos(COMPUTE * lat1) * sin(COMPUTE * lon1);
	
	x2 = cos(COMPUTE * lat2) * cos(COMPUTE * lon2);
	y2 = cos(COMPUTE * lat2) * sin(COMPUTE * lon2);
	
	z1 = sin(COMPUTE * lat1);
	z2 = sin(COMPUTE * lat2);
	
	return (EARTH_RADIUS * acos((x1 * x2) + (y1 * y2) + (z1 * z2))  * (1 + pMap->zoom));
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
		im = (id + ifin) / 2;
    
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

void Draw(way* w)
{
	Sint16 *vx, *vy;
	node_t* node;
	double longitude, latitude, minlat, maxlat, minlon, maxlon;
	int i, index, coord;
	
	maxlat = pBound->maxlat;
	minlat = pBound->minlat;
	maxlon = pBound->maxlon;
	minlon = pBound->minlon;
	
	for(i = 0; i < w->size; i++)
	{
		index = naive(w->ref[i]);
		
		if(index == FAILURE)
			continue;
		
		if((node = pRoot->arrayNodes[index])->type == ANYTHING)
			continue;
			
		if((node->latitude >= minlat) 
			&& (node->latitude <= maxlat) 
			&& (node->longitude <= maxlon)
			&& (node->longitude >= minlon))
			coord++;

	}
	
	vx = (Sint16*)malloc(coord * sizeof(*vx));
	vy = (Sint16*)malloc(coord * sizeof(*vy));
	coord = 0;
	
	for(i = 0; i < w->size; i++)
	{
		index = naive(w->ref[i]);
		
		if(!(index != FAILURE && (node = pRoot->arrayNodes[index])->type != ANYTHING))
			continue;;
			
		
		if((node->latitude >= minlat) 
			&& (node->latitude <= maxlat) 
			&& (node->longitude <= maxlon)
			&& (node->longitude >= minlon))
		{
				
			longitude = node->longitude;
			latitude = node->latitude;
			
			if(longitude < minlon) 
				longitude = minlon;
				
			if(latitude > maxlat)
				latitude = maxlat;
			
			vx[coord] = (Sint16)(pMap->width * (longitude-minlon)/(maxlon-minlon));
			vy[coord] = (Sint16)(pMap->height * (maxlat-latitude)/(maxlat-minlat));
			coord++;
		}
	}

	switch(w->type_primary)
	{
	case UNKNOW:
			break;
	case BUILDING:
			Draw_BUILDING(vx, vy, coord, w->type_secondary);
			break;
	case HIGHWAY:
			Draw_HIGHWAY(vx, vy, coord, w->type_secondary);
			break;
	case WATERWAY:
			Draw_WATERWAY(vx, vy, coord, w->type_secondary);
			break;
	case LEISURE:
			Draw_LEISURE(vx, vy, coord, w->type_secondary);
			break;
	case LANDUSE:
			Draw_LANDUSE(vx, vy, coord, w->type_secondary);
			break;
	case RAILWAY:
			Draw_RAILWAY(vx, vy, coord, w->type_secondary);
			break;
	case BRIDGE:
			Draw_BRIDGE(vx, vy, coord, w->type_secondary);
			break;
	default:
	 	/*Should not be reached*/
		break;
	}
	
	free(vx);
	free(vy);
}

void Draw_BUILDING(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{	
	filledPolygonRGBA(pRenderer, vx, vy, coord, 191, 174, 174, 100);
	polygonRGBA(pRenderer, vx, vy, coord, 0, 0, 0, 255);
}

void Draw_HIGHWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{
	int i;
	
	for(i = 0; i < coord - 1;i++)
      thickLineRGBA (pRenderer, vx[i], vy[i], vx[i+1], vy[i+1], coord, 100, 0, 0, 255);
}

void Draw_WATERWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{
	switch(type) 
	{
		case RIVER:
			break;
		case RIVERBANK:
			filledPolygonRGBA(pRenderer, vx, vy, coord, 181, 208, 208, 255);
			break;
		default:
			break;
	}
}

void Draw_LEISURE(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{
	switch(type) 
	{
		case PARK:
			filledPolygonRGBA(pRenderer, vx, vy, coord, 197, 240, 197, 255);
			break;
		case GARDEN:
			filledPolygonRGBA(pRenderer, vx, vy, coord, 207, 236, 168, 255);
			break;		
		default:
			break;
	}
}

void Draw_LANDUSE(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{

}


void Draw_RAILWAY(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{

}


void Draw_BRIDGE(Sint16 *vx, Sint16 *vy, int coord, type_t type)
{

}
