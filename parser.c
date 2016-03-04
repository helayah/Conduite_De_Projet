#include "parser.h"
#include "objs.h"

void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f) {
   /* xmlNodePtr n;
    int i = 0;
    for (n = noeud; n != NULL; n = n->next) {
        f(n);
        if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
            parcours_prefixe(n->children, f);
        }
        i++;
    }*/
}

void afficher_noeud(xmlNodePtr noeud) {
    /*if (noeud->type == XML_ELEMENT_NODE) {
        xmlChar *chemin = xmlGetNodePath(noeud);
        if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE) {
            xmlChar *contenu = xmlNodeGetContent(noeud);
            printf("%s -> %s\n", chemin, contenu);
            xmlFree(contenu);
        } else {
            printf("%s\n", chemin);
        }
        xmlFree(chemin);
    }*/
}

void dfs(xmlNodePtr node)
{/*
	node = node->xmlChildrenNode;
	
	while(node != NULL)
	{
	    if (node->children != NULL && node->children->type == XML_TEXT_NODE)
        {
            
            
            
        }
		node->next;
	}*/
}

struct node_t* node_children(xmlNodePtr node)
{
    struct node_t *root = NULL;
    xmlChar *id, *lat, *lon, *user, *uid, *version, *visible, *changeset, *timestamp;
    
    node = node->xmlChildrenNode;
    root = malloc(sizeof(struct node_t *));
    
    while(node != NULL)
    {
        if (strcmp((const char *) node->name, "node") == 0)
        {
            id = xmlGetProp(node, (const xmlChar *) "id");
            lat = xmlGetProp(node, (const xmlChar *) "lat");
            lon = xmlGetProp(node, (const xmlChar *) "lon");
            user = xmlGetProp(node, (const xmlChar *) "user");
            uid = xmlGetProp(node, (const xmlChar *) "uid");
            version = xmlGetProp(node, (const xmlChar *) "version");
            visible = xmlGetProp(node, (const xmlChar *) "visible");
            changeset = xmlGetProp(node, (const xmlChar *) "changeset");
            timestamp = xmlGetProp(node, (const xmlChar *) "timestamp");
            
            printf("id = %s\n", (char *) id);
            break;
            xmlFree(id);
            xmlFree(lat);
            xmlFree(lon);
            xmlFree(user);
            xmlFree(uid);
            xmlFree(version);
            xmlFree(visible);
            xmlFree(changeset);
            xmlFree(timestamp);
        }
        node = node->next;
    }
    
    return root;
}

int parse(char *str)
{
	xmlDocPtr doc;
  	xmlNodePtr root;
    struct node_t* node = NULL;
  	//xmlXPathContextPtr context;
	//xmlXPathObjectPtr result;
    int i = 1;
    
	if((doc = xmlParseFile(str)) == NULL)
	{
		
		return FAILURE;
	}
	
	if((root = xmlDocGetRootElement(doc)) == NULL)
	{

		xmlFreeDoc(doc);
		return FAILURE;
	}
	
    if((node = node_children(root)) == NULL)
    {
        xmlFreeDoc(doc);
		return FAILURE;
    }
	
	//parcours_prefixe(root, afficher_noeud);
	
	/*
	xmlChar *key;
	//child = root->xmlChildrenNode;
	key = xmlNodeListGetString(doc, root->xmlChildrenNode, 1);
	printf("keyword: %s\n", key);
	xmlFree(key);
	
	
	while(child != NULL)
	{
		if(i == 10)
			break;
			
		printf("%s\n", child->name);
		i++;
		
		child->next;
	}*/
	


	/*
	if(xmlStrcmp(root->name, (const xmlChar *) "osm"))
	{
		xmlFreeDoc(doc);
		return FAILURE;
	}
	
	xmlNodeGetContent(root);
	*/
	printf("Node = %d\n", i);
	free(node);
	xmlFreeDoc(doc);


	return SUCCESS;
}


/*
int parse(char *str)
{
	FILE* file = NULL;

	xmlFileOpen(str);
	

	if (read_xml(str) == FAILURE)
	{
		fprintf(stderr, "%s\n", READ_XML_FAILURE);
		return FAILURE;
	}
	if ((file = fopen(str, "r")) == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return FAILURE;
	}

	if (xmlFileClose(str) == FAILURE)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return FAILURE;
	}

	if (fclose(file) == FAILURE)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return FAILURE;
	}

	return SUCCESS;
}
*/

/*
int read_xml(char* name)
{
	xmlTextReaderPtr* reader = NULL;

	if ((reader = xmlReaderForFile(name, "utf-8", 0)) == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return FAILURE;
	}

	if (xmlTextReaderClose(reader) == FAILURE)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return FAILURE;
	}

	
}

int write_xml(char* name)
{
	xmlTextWriterPtr writer;
}*/
