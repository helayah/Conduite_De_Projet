#include "parser.h"
<<<<<<< HEAD

extern root* Root;

int Root_GetSizeAndBound(xmlNodePtr node)
{
=======
#include "objs.h"
#include "errs.h"

extern root* Root;

root* Root_GetSizeAndBound(xmlNodePtr node)
{
	root *r = NULL;
>>>>>>> origin/master
	bounds b;
	xmlChar *minlat, *minlon, *maxlat, *maxlon;
	uint32_t nb_node = 0, nb_way = 0;
	
	node = node->children;
	node = node->next;
			
	if (strcmp((const char *) node->name, "bounds") == 0)
    {
		minlat = xmlGetProp(node, (const xmlChar *) "minlat");
        minlon = xmlGetProp(node, (const xmlChar *) "minlon");
        maxlat = xmlGetProp(node, (const xmlChar *) "maxlat");
        maxlon = xmlGetProp(node, (const xmlChar *) "maxlon");
		
<<<<<<< HEAD
		b.minlat = (double)atof((char *)minlat);
		b.minlon = (double)atof((char *)minlon);
		b.maxlat = (double)atof((char *)maxlat);
		b.maxlon = (double)atof((char *)maxlon);
=======
		b.minlat = atof((char *)minlat);
		b.minlon = atof((char *)minlon);
		b.maxlat = atof((char *)maxlat);
		b.maxlon = atof((char *)maxlon);
>>>>>>> origin/master
		
		xmlFree(minlat);
        xmlFree(minlon);
		xmlFree(maxlat);
		xmlFree(maxlon);
		
<<<<<<< HEAD
=======
		//Bound_Display(&b);
		
>>>>>>> origin/master
		while(node != NULL)
		{
			if (strcmp((const char *) node->name, "way") == 0)
				nb_way++;
			else
				if (strcmp((const char *) node->name, "node") == 0)
					nb_node++;
			
			node = node->next;
		}
<<<<<<< HEAD
		Root = Root_Init(nb_node, nb_way, &b);

		return SUCCESS;
	}
	return FAILURE;
}

int Root_GetNodes(xmlNodePtr node, int index)
{
	xmlNodePtr child;
    xmlChar *idNode, *lat, *lon, *user, *uid, *version, *visible, *changeset, *timestamp;
    xmlChar *idWay, *ref;
    node_t* n = NULL;
	long l;
	
    while(node != NULL)
    {	
    	if (!xmlStrcmp(node->name, (const xmlChar *) "node"))
		{
			idNode = xmlGetProp(node, (const xmlChar *) "id");
			lat = xmlGetProp(node, (const xmlChar *) "lat");
			lon = xmlGetProp(node, (const xmlChar *) "lon");
			
			n = Node_Init((uint32_t)strtoul((char *)idNode, NULL, 0), (double)atof((char *)lat), (double)atof((char *)lon));
			Root->arrayNode[index++] = n;
			
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
	
	while(node != NULL)
	{
		if(!xmlStrcmp(node->name, (const xmlChar *) "way"))
		{
			idWay = xmlGetProp(node, (const xmlChar *) "id");
			Root->arrayWays[index_way++] = Ways_Init((uint32_t)strtoul((char *)idWay, NULL, 0), (int)xmlChildElementCount(node));
			xmlFree(idWay);
		}
		
		
		if(!xmlStrcmp(node->name, (const xmlChar *) "nd") && !xmlStrcmp(node->parent->name, (const xmlChar *) "way"))
		{
			ref = xmlGetProp(node, (const xmlChar *) "ref");
			Root->arrayWays[index_way - 1]->ref[index_ref++] = (uint32_t)strtoul((char *)ref, NULL, 0);
			xmlFree(ref);
		}
		
		if(!xmlStrcmp(node->name, (const xmlChar *) "tag") && !xmlStrcmp(node->parent->name, (const xmlChar *) "way"))
		{
			k = xmlGetProp(node, (const xmlChar *) "k");
			v = xmlGetProp(node, (const xmlChar *) "v");	
			
			if(!xmlStrcmp(k, (const xmlChar *) "building"))
			{
				Root->arrayWays[index_way - 1]->type = BUILDING;
			}
			
			if(!xmlStrcmp(k, (const xmlChar *) "leisure"))
			{
				Root->arrayWays[index_way - 1]->type = LEISURE;
			}
			
			if(!xmlStrcmp(k, (const xmlChar *) "waterway"))
			{
				Root->arrayWays[index_way - 1]->type = WATERWAY;
			}
			
			if(!xmlStrcmp(k, (const xmlChar *) "highway"))
			{
				Root->arrayWays[index_way - 1]->type = HIGHWAY;
			}
			
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


int parse(char *file)
{
	xmlDocPtr doc;
  	xmlNodePtr nodePtr;
    
	if((doc = xmlParseFile(file)) == NULL)
	{
		fprintf(stdout, "%s\n", PARSE_FILE_FAILURE);
		return FAILURE;
	}

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		fprintf(stdout, "%s\n", GET_ROOT_ELEMENT_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
	
	if (xmlStrcmp(nodePtr->name, (const xmlChar *) "osm"))
	{
		fprintf(stdout, "%s\n", NOT_AN_OS_FILE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
	
	if(Root_GetSizeAndBound(nodePtr) == FAILURE)
    {
		fprintf(stdout, "%s\n", GET_SIZE_AND_BOUND);
        xmlFreeDoc(doc);
		return FAILURE;
    }

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		fprintf(stdout, "%s\n", PARSING_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}

	if(Root_GetNodes(nodePtr, 0) == FAILURE)
    {
		fprintf(stdout, "%s\n", ROOT_GET_FAILURE);
        xmlFreeDoc(doc);
		return FAILURE;
    }
    
    if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		fprintf(stdout, "%s\n", PARSING_FAILURE);
		xmlFreeDoc(doc);
		return FAILURE;
	}
    
    if(Root_GetWays(nodePtr, 0, 0) == FAILURE)
    {
		fprintf(stdout, "%s\n", ROOT_GET_FAILURE);
        xmlFreeDoc(doc);
		return FAILURE;
    }
	
	xmlFreeDoc(doc);

	return SUCCESS;
}

=======
		
		return (Root = Root_Init(nb_node, nb_way, &b));
	}
	return NULL;
}

root* Root_Get(root* r, xmlNodePtr node)
{
	node_t* n = NULL;
    xmlChar *idNode, *lat, *lon, *user, *uid, *version, *visible, *changeset, *timestamp;
    xmlChar *idWay;
	node = node->children;
	int i = 0;
	
    while(node != NULL)
    {
        if (strcmp((const char *) node->name, "node") == 0)
        {
            idNode = xmlGetProp(node, (const xmlChar *) "id");
            lat = xmlGetProp(node, (const xmlChar *) "lat");
            lon = xmlGetProp(node, (const xmlChar *) "lon");
            /*user = xmlGetProp(node, (const xmlChar *) "user");
            uid = xmlGetProp(node, (const xmlChar *) "uid");
            version = xmlGetProp(node, (const xmlChar *) "version");
            visible = xmlGetProp(node, (const xmlChar *) "visible");
            changeset = xmlGetProp(node, (const xmlChar *) "changeset");
            timestamp = xmlGetProp(node, (const xmlChar *) "timestamp");*/
			//Node_Display(n = Node_Init((uint32_t)strtoul((char *)idNode, NULL, 0), atof(lat), atof(lon));
			n = Node_Init((uint32_t)strtoul((char *)idNode, NULL, 0), (double)atof(lat), (double)atof(lon));
			r->arrayNode[i++] = n;
			//Node_Display(n);
            xmlFree(idNode);
            xmlFree(lat);
            xmlFree(lon);
            /*xmlFree(user);
            xmlFree(uid);
            xmlFree(version);
            xmlFree(visible);
            xmlFree(changeset);
            xmlFree(timestamp);*/
        }
        node = node->next;
    }
	
    return r;
}

root* parse(char *file)
{
	xmlDocPtr doc;
  	xmlNodePtr nodePtr;
    
	if((doc = xmlParseFile(file)) == NULL)
	{
		fprintf(stdout, "%s\n", PARSE_FILE_FAILURE);
		return NULL;
	}

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		fprintf(stdout, "%s\n", GET_ROOT_ELEMENT_FAILURE);
		xmlFreeDoc(doc);
		return NULL;
	}
	
	if (xmlStrcmp(nodePtr->name, (const xmlChar *) "osm"))
	{
		fprintf(stdout, "%s\n", NOT_AN_OS_FILE);
		xmlFreeDoc(doc);
		return NULL;
	}
		
	if(Root_GetSizeAndBound(nodePtr) == NULL)
    {
		fprintf(stdout, "%s\n", GET_SIZE_AND_BOUND);
        xmlFreeDoc(doc);
		return NULL;
    }

	if((nodePtr = xmlDocGetRootElement(doc)) == NULL)
	{
		fprintf(stdout, "%s\n", PARSING_FAILURE);
		xmlFreeDoc(doc);
		return NULL;
	}
	
	if((Root = Root_Get(Root, nodePtr)) == NULL)
    {
		fprintf(stdout, "%s\n", ROOT_GET_FAILURE);
        xmlFreeDoc(doc);
		return NULL;
    }

	//Root_Display(Root);
	
	xmlFreeDoc(doc);

	return Root;
}
>>>>>>> origin/master
