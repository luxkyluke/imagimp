#ifndef _CALQUE_H_
#define _CALQUE_H_

#include "LUT.h"
#include "Pixel.h"
#include "Fusion.h"
#include "PPM.h"
#include "Histogramme.h"
#include "sdl_tools.h"
#include "LutOption.h"
#include "Effet.h"


typedef struct Calque{
	Fusion fusion;
	Pixel** pixels;
	LUT* listLuts;
	float alpha;
	struct Calque* next;
	struct Calque* prev;
	int height, width;
    Histogramme* histogramme;
	unsigned int id;
    int isSelected;
    Effet effet;
} Calque;

void remplirCalqueCouleur(Calque* calque, Pixel p);
Calque* makeCalque(int w, int h, float op);
Calque* getCalqueById(Calque* c, int id);
Calque* copyCalque(Calque *c) ;
Calque* addNewCalque(Calque* c, float op);
void addCalque(Calque* c, Calque* c2) ;
bool existLUTCalqueType(Calque *c, LutOption type);
void addLUTCalque(Calque *c, LutOption lut, int val);
void removeCalque(Calque* c) ;
int chargerImageCalque(Calque* c, const char * pathImg, int width, int height, float op);
Calque* appliquerEffet(Calque* c) ;
void fusionnerMultiplicationCalque2a2(Calque *ret, Calque *c2) ;
bool isOnEffect(Calque *c);
void resetEffet(Calque *c);
void fusionnerAdditiveCalque2a2(Calque *ret, Calque *c2) ;
Calque* fusionnerCalque(Calque* c);
Calque* appliqueLUT(Calque* calque, LUT* L) ;
Calque* appliquerAllLUT(Calque* calque) ;
void freeCalque(Calque* c) ;
void freeCalque_r(Calque* c);
void drawCalqueHistogramme(Calque* c) ;
void saveCalque(Calque* c, char *pathImg) ;
void drawCalque(Calque *c);
Calque* noirEtBlanc(Calque* C) ;
Calque* appliquerSepia(Calque* C);

#endif
