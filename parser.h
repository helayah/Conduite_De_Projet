#ifndef PARSER_INCLUDED_H
#define PARSER_INCLUDED_H

#include "libs.h"
#include "errs.h"
#include "objs.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <sys/types.h>
#include <fcntl.h>

root* Root_GetSizeAndBound(xmlNodePtr node);
root* Root_Get(root* r, xmlNodePtr node);

root* parse(char* file);

#endif
