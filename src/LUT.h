#ifndef LUT_H_
#define LUT_H_

#include "bool.h"
#include <stdlib.h>

typedef struct LUT{
	int lut[256];
	LUT* prev;
	LUT* next;
}LUT;

LUT* MakeLUT();
bool LUTIsEmpty(LUT* list);
void addNode(LUT* list, int lut[256]);

#endif
