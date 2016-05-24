#ifndef _CALQUE_H_
#define _CALQUE_H_

#include "LUT.h"
#include "Pixel.h"
#include "Fusion.h"
#include "PPM.h"
#include "Histogramme.h"
#include "sdl_tools.h"
#include "LutOption.h"


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
} Calque;

Calque* makeCalque(int w, int h, float op);
Calque* getNextCalque(Calque* c);
Calque* getPrevCalque(Calque* c);
Calque* getCalqueById(Calque* c, int id);
Calque* copyCalque(Calque *c);
int chargerImageCalque(Calque* c, char * pathImg, int width, int height, float op);
void setCalqueAlpha(Calque* c, float alpha);
void setFusion(Calque* c, Fusion fusion);
void removeCalque(Calque* c);
bool calqueIsEmpty(Calque* c);
int addLUTCalque(Calque *c, LutOption l, int val);
Calque* addNewCalque(Calque* c, float op);
void fusionCalqueDefinitive(Calque **calque);
void drawCalqueHistogramme(Calque* c);
void addCalque(Calque* c, Calque* c2);
Calque* fusionnerCalque(Calque* c);
Calque* appliquerLUTById(Calque* calque, int id);
Calque* appliquerAllLUT(Calque* calque);
void drawCalque(Calque* c);
void suppCalque(Calque* c);
void freeCalque_r(Calque* c);
void freeCalque(Calque* c);
void saveCalque(Calque* c, char * pathImg);

Calque* noirEtBlanc(Calque* C);



#endif
