#ifndef _LUT_H_
#define _LUT_H_

#include "bool.h"
#include <stdlib.h>

typedef struct LUT{
	int lut[256];
	struct LUT* prev;
	struct LUT* next;
}LUT;


LUT* initLUT();
bool LUTIsEmpty(LUT* list);
void addNode(LUT* list, int lut[256]);

#endif
