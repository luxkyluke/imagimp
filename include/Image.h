#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Calque.h"
#include <SDL/SDL.h>
#include "PPM.h"
#include "LUT.h"
#include "Pixel.h"
#include "LutOption.h"


typedef struct Image{
	Calque* listCalques;
	Calque* calque_resultat;
} Image;




Image* makeImage(int width, int height) ;
int chargerImage(Image* img, const char * pathImg, int width, int height, float op) ;
void addEffetCalqueById(Image* img, int id, Effet effet);
void drawImageHistogramme(Image* img) ;
void addLUTCalqueById(Image* img, int id, LutOption lut, int val) ;
void modifyOppacityCalqueById(Image *img, int id, float alpha);
void drawImage(Image* img, SDL_Surface* framebuffer);
void freeImage(Image* img);
void saveImage(Image* img, char* savePath);
void fusionnerCalquesImage(Image* img);
void resetOpacityCalqueById(Image* img, int id);
void switchEffectById(Image * img, int id, Effet effet);
void afficheCalqueById(Image* img, int calque_id) ;
void removeClaqueById(Image* img, int id) ;

#endif
