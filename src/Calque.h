#ifndef CALQUE_H_
#define CALQUE_H_

#include "LUT.h"
#include "Pixel.h"

typedef struct Calque{
	int fusion;
	Pixel pixels[][];
	Image image;
	LUT* listLuts;
	float alpha;
	Calque* next;
	Calque* prev;
} Calque;

void makeCalque(Calque* c);
void setCalqueAlpha(float alpha);
//- modifier fonction de mélange du calque
//- supprimer le calque courant (impossible si un seul calque)


#endif
