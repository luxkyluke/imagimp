#ifndef CALQUE_H_
#define CALQUE_H_

#include "LUT.h"
#include "Pixel.h"
#include "Fusion.h"

typedef struct Calque{
	Fusion fusion;
	Pixel** pixels;
	LUT* listLuts;
	float alpha;
	Calque* next;
	Calque* prev;
	int height, width;
} Calque;

Calque* makeCalque();
Calque* getNextCalque(Calque* c);
Calque* getPrevCalque(Calque* c);
void setCalqueAlpha(Calque* c, float alpha);
void setFusion(Calque* c, Fusion fusion);
void emoveCalque(Calque* c);
bool calqueIsEmpty(Calque* c);
void addCalque(Calque* c);
void fusionnerCalquer(Calque* c);


#endif
