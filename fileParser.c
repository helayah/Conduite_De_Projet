#include <stdio.h>
#include "env.c"
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <math.h>
#define PI 3.14
#define R 6371


//Formule magique?: (minlat(bounds)-lat(node))/minlat(bounds)-maxlat(node)= coef1
//lat(node)=largeurfenetreenpixel*coef1
//(minlong(bounds)-long(node))/minlong(bounds)-maxlong(node)= coef2
//long(node)=hateurfenetrepixel*coef2


void afficher_noeud(xmlNodePtr noeud);

struct node * getNodes(xmlNodePtr noeud) {
  xmlNodePtr n;
  struct node *p_head=NULL;
  for (n = noeud; n != NULL; n = n->next) {
    xmlChar * s;xmlChar * s1;xmlChar * s2;    
    s = xmlGetProp(n,(const xmlChar *) "id");
    s1 =xmlGetProp(n,(const xmlChar *) "lon");
    s2 =xmlGetProp(n,(const xmlChar *) "lat");
    if (strcmp(n->name,(const xmlChar *)"node")==0){
      printf(" id : %s - longitude : %s - latitude :%s\n",(char *)s,s1,s2);
      p_head=add_end_node(p_head,atoi(s),(double)atof(s1),(double)atof(s2));
    }
    
    xmlFree(s);
    xmlFree(s1);
    xmlFree(s2);
    if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
      struct node *p =getNodes(n->children);
	while (p!=NULL){
	  p_head=add_end_node(p_head,p->id,p->lon,p->lat);
	  p=p->p_next;
	}
    }
  }
  return p_head;
}

struct bounds * getbounds(xmlNodePtr rac){

  xmlNodePtr n;
	struct bounds *b = malloc (sizeof *b);
  
  for (n = rac; n != NULL; n = n->next) {
	if (strcmp(n->name,(const xmlChar *)"bounds")==0){
	xmlChar * s1;xmlChar * s2;xmlChar * s3;xmlChar * s4;
	s1 = xmlGetProp(n,(const xmlChar *) "minlat");
        s2 =xmlGetProp(n,(const xmlChar *) "minlon");
        s3 =xmlGetProp(n,(const xmlChar *) "maxlat");
	s4 = xmlGetProp(n,(const xmlChar *) "maxlon");
	
	b->minlat=(double)atof(s1);
	b->minlon=(double)atof(s2);
	b->maxlat=(double)atof(s3);
	b->maxlon=(double)atof(s4);
	 printf("minlat : %s - minlon : %s - maxlat :%s - maxlong : %s\n",(char *)s1,s2,s3,s4);
	break;
	}
	}
	return b;
}


double * get_dimensions(xmlNodePtr noeud){
  xmlNodePtr n;
  double * tab ;
  tab=(double * )malloc(4*sizeof(double));  
  int i;
  for (n = noeud,i=0; n != NULL; n = n->next,i++) {
    
    if (strcmp(n->name,(const xmlChar *)"bounds")==0){
      xmlChar * s0;
      xmlChar * s1;
      xmlChar * s2;
      xmlChar * s3;
      s0=xmlGetProp(n,(const xmlChar *) "minlat");
      s1=xmlGetProp(n,(const xmlChar *) "maxlat");
      s2=xmlGetProp(n,(const xmlChar *) "minlon");
      s3=xmlGetProp(n,(const xmlChar *) "maxlon");
      double minlat=(double)atof(s0);
      double maxlat=(double)atof(s1);
      double minlon=(double)atof(s2);
      double maxlon=(double)atof(s3);	
      //MINLAT - MAXLAT -MINLON - MAXLON
      tab[0]=minlat;
      tab[1]=maxlat;
      tab[2]=minlon;
      tab[3]=maxlon;
      free(s0);free(s1);free(s2);free(s3);	
      // printf(" minlat : %f - maxlat : %f - minlon :%f - maxlon %f\n",minlat,maxlat,minlon,maxlon);
      return tab;	
    }
    if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
      tab= get_dimensions(n->children);
    }
  }
  return tab;
}

struct ways * getWays(xmlNodePtr noeud,int id) {
  xmlNodePtr n;    
  struct ways *w_head=NULL;
  for (n = noeud; n != NULL; n = n->next) {
    //afficher_noeud(n);
    //recuperer les nodes ac id et lon et lat
    xmlChar * s;xmlChar * s1; 
    s = xmlGetProp(n,(const xmlChar *) "id");
    s1 = xmlGetProp(n,(const xmlChar *) "ref");    
    if (strcmp(n->name,(const xmlChar *)"way")==0){
      id=atoi(s);
    }
    if (strcmp(n->name,(const xmlChar *)"nd")==0){
      //printf("nd ref : %s --",s1);
      w_head=add_end_way(w_head,id,atoi(s1));
    }
    xmlFree(s);xmlFree(s1);
    if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
      struct ways * w=getWays(n->children,id);
      while (w!=NULL){
	w_head=add_end_way(w_head,w->id,w->ref);
	w=w->w_next;
      }
    }
  }
  return w_head;
}





void afficher_noeud(xmlNodePtr noeud) {
  if (noeud->type == XML_ELEMENT_NODE) {
    xmlChar *chemin = xmlGetNodePath(noeud);
    if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE) {
      xmlChar *contenu =xmlNodeGetContent(noeud);
      printf("%s ****->**** %s ->**** %s\n", chemin, contenu,noeud->name);
      xmlFree(contenu);
    } else {
      printf("%s\n", chemin);
    }
    xmlFree(chemin);
  }
}


int main() {
  xmlDocPtr doc;
  xmlNodePtr racine;
  
  // Ouverture du fichier XML
  doc = xmlParseFile("denver.osm");
  
  if (doc == NULL) {
    fprintf(stderr, "Document XML invalide\n");
    return EXIT_FAILURE;
    }
  // Récupération de la racine
  racine = xmlDocGetRootElement(doc);
  
  if (racine == NULL) {
    fprintf(stderr, "Document XML vierge\n");
    xmlFreeDoc(doc);
    return EXIT_FAILURE;
  }
  if (xmlStrcmp(racine->name, (const xmlChar *) "osm")) {
    fprintf(stderr,"Mauvais type de document !! , root node != osm");
    xmlFreeDoc(doc);
    return 1;
  }
  printf("La racine du document est : %s\n", racine->name);    
  struct node *p_head = getNodes(racine);
  //display_node(p_head);
  struct ways * w_head=getWays(racine,0);
  //display_way(w_head);
  printf("\n\n");
  double * tab;
  tab=(double *)malloc(4*sizeof(double));
  tab =get_dimensions(racine);	
  
	//on va avoir un ensemble de node en une liste,un ensemble de way formant des chemins en un petit ensemble de node relié entre eux que l'on chope dans la liste des node selon leur id.

  //draw(p_head,w_head,tab[0],tab[1],tab[2],tab[3]);
  free(tab);
  // Libération de la mémoire
  xmlFreeDoc(doc);
   
  return EXIT_SUCCESS;
}
