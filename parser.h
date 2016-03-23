#ifndef PARSER_INCLUDED_H
#define PARSER_INCLUDED_H

#include "libs.h"
#include "errs.h"
#include "objs.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <sys/types.h>
#include <fcntl.h>

int Root_GetSizeAndBound(xmlNodePtr node);
int Root_GetNodes(xmlNodePtr node, int index);
int Root_GetWays(xmlNodePtr node, int index_way, int index_ref);

int parse(char* file);

#endif
