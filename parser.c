#include "parser.h"

extern Root* pRoot;

int parse(char* file)
{
	xmlDocPtr doc;
  	xmlNodePtr nodePtr;
  	
  	if((doc = xmlParseFile(file)) == NULL)
	{
		//fprintf(stdout, "%s\n", PARSE_FILE_FAILURE);
		return FAILURE;
	}

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		//fprintf(stdout, "%s\n", GET_ROOT_ELEMENT_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
	
	if (xmlStrcmp(nodePtr->name, (const xmlChar *) "osm"))
	{
		//fprintf(stdout, "%s\n", NOT_AN_OS_FILE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
	
	if(Root_GetSizeAndBound(nodePtr) == FAILURE)
    {
		//fprintf(stdout, "%s\n", GET_SIZE_AND_BOUND);
        xmlFreeDoc(doc);
		return FAILURE;
    }

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		//fprintf(stdout, "%s\n", PARSING_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}

	if(Root_GetNodes(nodePtr, 0) == FAILURE)
    {
		//fprintf(stdout, "%s\n", ROOT_GET_FAILURE);
        xmlFreeDoc(doc);
		return FAILURE;
    }
    
    if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		//fprintf(stdout, "%s\n", PARSING_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
    
    if(Root_GetWays(nodePtr, 0, 0) == FAILURE)
    {
		//fprintf(stdout, "%s\n", ROOT_GET_FAILURE);
        xmlFreeDoc(doc);
		return FAILURE;
    }
	
	xmlFreeDoc(doc);
	
	return SUCCESS;
}

int Root_GetSizeAndBound(xmlNodePtr node)
{
	double minlat, minlon, maxlat, maxlon;
	xmlChar *minlt, *minln, *maxlt, *maxln;
	int nb_node = 0, nb_way = 0;
	node = node->children;
	node = node->next;
	

	if (strcmp((const char *) node->name, "bounds") == 0)
    {
		minlt = xmlGetProp(node, (const xmlChar *) "minlat");
        minln = xmlGetProp(node, (const xmlChar *) "minlon");
        maxlt = xmlGetProp(node, (const xmlChar *) "maxlat");
        maxln = xmlGetProp(node, (const xmlChar *) "maxlon");
		
		minlat = atof((const char *)minlt);
		minlon = atof((const char *)minln);
		maxlat = atof((const char *)maxlt);
		maxlon = atof((const char *)maxln);
		
		Bound_Init(minlat, minlon, maxlat, maxlon);
		
		xmlFree(minlt);
        xmlFree(minln);
		xmlFree(maxlt);
		xmlFree(maxln);
		
		while(node != NULL)
		{
			if (strcmp((const char *) node->name, "way") == 0)
				nb_way++;
			else
				if (strcmp((const char *) node->name, "node") == 0)
					nb_node++;
			
			node = node->next;
		}
		
		Root_Init(nb_node, nb_way);

		return SUCCESS;
	}
	return FAILURE;
}

int Root_GetNodes(xmlNodePtr node, int index)
{
    xmlChar *idNode, *lat, *lon;
    node_t* n = NULL;
    double lt, ln;
    uint32_t id;
    
	while(node != NULL)
    {	
    	if (!xmlStrcmp(node->name, (const xmlChar *) "node"))
		{
			idNode = xmlGetProp(node, (const xmlChar *) "id");
			lat = xmlGetProp(node, (const xmlChar *) "lat");
			lon = xmlGetProp(node, (const xmlChar *) "lon");
			
			id = strtoul((const char *)idNode, NULL, 0);
			lt = atof((const char *)lat);
			ln = atof((const char *)lon);
			
			n = Node_Init(id, lt, ln);
			pRoot->arrayNodes[index++] = n;
			
			xmlFree(idNode);
			xmlFree(lat);
			xmlFree(lon);
		}

		if ((node->type == XML_ELEMENT_NODE) && (node->children != NULL))
		{
			Root_GetNodes(node->children, index);
    	}
		
        node = node->next;
    }
	
    return SUCCESS;
}

int Root_GetWays(xmlNodePtr node, int index_way, int index_ref)
{
	xmlChar *idWay, *ref, *k, *v;
	way* w = NULL;
	uint32_t rf, id;
	int nbChild;
	
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name, (const xmlChar *) "way"))
		{
			idWay = xmlGetProp(node, (const xmlChar *) "id");
			
			id = strtoul((const char *)idWay, NULL, 0);
			nbChild = (int)xmlChildElementCount(node);
			
			w = Ways_Init(id, nbChild);
			pRoot->arrayWays[index_way++] = w;
			
			xmlFree(idWay);
		}
			
		if(!xmlStrcmp(node->name, (const xmlChar *) "nd") && !xmlStrcmp(node->parent->name, (const xmlChar *) "way"))
		{
			ref = xmlGetProp(node, (const xmlChar *) "ref");
			
			rf = strtoul((const char *)ref, NULL, 0);
			pRoot->arrayWays[index_way - 1]->ref[index_ref++] = rf;
			
			xmlFree(ref);
		}
		
		if(!xmlStrcmp(node->name, (const xmlChar *) "tag") && !xmlStrcmp(node->parent->name, (const xmlChar *) "way"))
		{
			k = xmlGetProp(node, (const xmlChar *) "k");
			v = xmlGetProp(node, (const xmlChar *) "v");	
			
			if(!xmlStrcmp(k, (const xmlChar *) "building"))
				pRoot->arrayWays[index_way - 1]->type = BUILDING;
			
			if(!xmlStrcmp(k, (const xmlChar *) "leisure"))
				pRoot->arrayWays[index_way - 1]->type = LEISURE;
			
			if(!xmlStrcmp(k, (const xmlChar *) "waterway"))
				pRoot->arrayWays[index_way - 1]->type = WATERWAY;
			
			if(!xmlStrcmp(k, (const xmlChar *) "highway"))
				pRoot->arrayWays[index_way - 1]->type = HIGHWAY;
			
			xmlFree(k);
			xmlFree(v);
		}
	
		if ((node->type == XML_ELEMENT_NODE) && (node->children != NULL))
		{
			Root_GetWays(node->children, index_way, index_ref);
    	}
    	
		node = node->next;
	}
	return SUCCESS;
}
