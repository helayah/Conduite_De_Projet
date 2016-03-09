#include "parser.h"
#include "objs.h"
#include "errs.h"

extern root* Root;

root* Root_GetSizeAndBound(xmlNodePtr node)
{
	root *r = NULL;
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
		
		b.minlat = atof((char *)minlat);
		b.minlon = atof((char *)minlon);
		b.maxlat = atof((char *)maxlat);
		b.maxlon = atof((char *)maxlon);
		
		xmlFree(minlat);
        xmlFree(minlon);
		xmlFree(maxlat);
		xmlFree(maxlon);
		
		//Bound_Display(&b);
		
		while(node != NULL)
		{
			if (strcmp((const char *) node->name, "way") == 0)
				nb_way++;
			else
				if (strcmp((const char *) node->name, "node") == 0)
					nb_node++;
			
			node = node->next;
		}
		
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
