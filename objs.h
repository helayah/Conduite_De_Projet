#ifndef OBJS_INCLUDED_H
#define OBJS_INCLUDED_H

#include "libs.h"


typedef struct position {
	float longitute;
	float latitude;
} position;

typedef struct user {
	char* name;
	uint16_t id;
} user;


typedef struct node_t {
	uint32_t id;
	struct position pos;
	struct user puser;
	int visible;
	unsigned short version;
	uint32_t changeset;
	time_t timestamp;
	struct node_t* pnext;
} node_t;

/*

typedef struct bounds {


} bounds;

typedef struct tag {
	char* k;
	char* v;
} tag;

typedef struct way {

} way; 

typedef struct highway {

} highway;

*/

#endif
