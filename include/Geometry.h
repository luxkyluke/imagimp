#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "common.h"
#include "Color3f.h"


#define CLAMP(x, min, max) MAX(min, MIN(max, x))
#define EPSILON 0.0005
#define PI 3.14


int IsZero(float x);
void dessinCercle(int n, int fill);
#endif
