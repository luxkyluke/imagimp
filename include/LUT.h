#ifndef _LUT_H_
#define _LUT_H_

#include "bool.h"
#include <stdlib.h>
#include <stdio.h>
#include "LutOption.h"

typedef struct LUT{
	int lut[256];
	struct LUT* prev;
	struct LUT* next;
	LutOption type;

}LUT;

void initLUT(int* lut);
LUT* makeLUT();
bool LUTIsEmpty(LUT* list);
void addLUT(LUT* list, LUT *l, LutOption type);
void deleteLUT(LUT** list);
void removeLUTByType(LUT* l, LutOption type);
bool existLUTByType(LUT* l, LutOption type);
LUT* copyLUT(LUT* l);
LUT* copyLUT_r(LUT* l);

void INVERT(LUT* L);
void ADDLUM(LUT* L, int l);
void DIMLUM(LUT* L, int l);
void ADDCON(LUT* L, int c);
void DIMCON(LUT* L, int c);

LUT* fusionnerLut(LUT* l);
void freeLUT(LUT** L);
void viderLUT (LUT* liste);


#endif
