#ifndef PARSER_INCLUDED_H
#define PARSER_INCLUDED_H

#include "libs.h"
#include "errs.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <sys/types.h>
#include <fcntl.h>

typedef void (*fct_parcours_t)(xmlNodePtr);

void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f);
void afficher_noeud(xmlNodePtr noeud);

struct node_t* node_children(xmlNodePtr node);

int parse(char* str);

#endif
