#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Calque.h"
#include <SDL/SDL.h>
//#include "sdl_tools.h"
#include "PPM.h"
#include "LUT.h"
#include "Pixel.h"
#include "LutOption.h"


#define HEIGHT 1080
#define WIDTH 1920

typedef struct Image{
	Calque* listCalques;
	Calque* calque_resultat;
} Image;

Image* makeImage(int width, int height);
int chargerImage(Image* img, char * pathImg, int width, int height, float op);
void saveImage(Image* img, char* savePath);
void printImage(Image* img, SDL_Surface* framebuffer);
void freeImage(Image* img);
void appliqueLUTCalqueId(Image* img, int id);
void appliqueLUTCalqueByIds(Image* img, int calque_id, int lut_id);
void appliqueAllLUTCalqueById(Image* img, int id);
int addLUTCalqueById(Image* img, int id, LutOption lut, int val);
void updateImage(Image* img);
void drawImageHistogramme(Image* img);

#endif
