#ifndef IMAGE_H_
#define IMAGE_H_

#include "Claque.h"

typedef struct Image{
	Calque calque1;
	Calque calque2;	// ICI LISTE DBT CHAINEE DE CALQUES
	Calque calque3;
} Image;

void chargerImage(char * pathImg);
void saveImage(char* savePath);
Calque* getNextCalque(Image* img);
Calque* getPrevCalque(Image* img);

#endif
