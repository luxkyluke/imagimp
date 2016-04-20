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
bool IsLUTEmpty(LUT* list);
void addLUT(LUT* list, int lut[256]);
void deleteLUT(LUT* list);

int* INVERT(LUT* L);
int* ADDLUM(LUT* L, int l);
int* DIMLUM(LUT* L, int l);
int* ADDCON(LUT* L, int c);
int* DIMCON(LUT* L, int c);

#endif
