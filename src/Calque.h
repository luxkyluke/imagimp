#ifndef _CALQUE_H_
#define _CALQUE_H_

#include "LUT.h"
#include "Pixel.h"
#include "Fusion.h"
#include "PPM.h"


typedef struct Calque{
	Fusion fusion;
	Pixel** pixels;
	LUT* listLuts;
	float alpha;
	struct Calque* next;
	struct Calque* prev;
	int height, width;
	unsigned int ind;
} Calque;

Calque* makeCalque(int w, int h);
Calque* getNextCalque(Calque* c);
Calque* getPrevCalque(Calque* c);
void chargerImageCalque(Calque* c, char * pathImg, int width, int height);
void setCalqueAlpha(Calque* c, float alpha);
void setFusion(Calque* c, Fusion fusion);
void removeCalque(Calque* c);
bool calqueIsEmpty(Calque* c);
void addCalque(Calque* c);
void fusionnerCalque(Calque* c);
void appliquerLUT(LUT* L, Calque* calque);
void suppCalque(Calque* c);


#endif
