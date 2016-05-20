#ifndef _LUT_H_
#define _LUT_H_

#include "bool.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct LUT{
	int lut[256];
	struct LUT* prev;
	struct LUT* next;
}LUT;


LUT* makeLUT();
bool IsLUTEmpty(LUT* list);
void addLUT(LUT* list, int lut[256]);
void deleteLUT(LUT* list);

void INVERT(LUT* L);
void ADDLUM(LUT* L, int l);
void DIMLUM(LUT* L, int l);
void ADDCON(LUT* L, int c);
void DIMCON(LUT* L, int c);

void fusionnerLut(LUT* l);
void freeLUT(LUT* L);




#endif
