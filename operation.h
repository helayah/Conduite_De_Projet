#ifndef OPERATION_INCLUDED_H
#define OPERATION_INCLUDED_H

#include "libs.h"
#include "errs.h"
#include "objs.h"
#include "interface.h"
#include <math.h>

#define PI 3.14
#define DEFAULT_INDEX -1

double deg2rad(double deg);
double rad2deg(double rad);
int distanceCalculation(double lat1, double lon1, double lat2, double lon2);

void draw(ways* way);

void echanger(uint32_t *t, int i, int j);
int partition(uint32_t *t, int deb, int fin);
void tri_rapide_bis(uint32_t *t, int debut, int fin);
void tri_rapide(uint32_t *t, int n);

int naive(uint32_t id);
int dichotomie(uint32_t id_a_trouver);


#endif

