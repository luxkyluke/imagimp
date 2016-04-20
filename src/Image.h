#ifndef IMAGE_H_
#define IMAGE_H_

#include "Claque.h"

typedef struct Image{
	Calque* listCalques;
} Image;

void chargerImage(char * pathImg);
void saveImage(char* savePath);


#endif
