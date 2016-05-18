#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Calque.h"
#include <SDL/SDL.h>
#include "sdl_tools.h"
#include "PPM.h"
#include "LUT.h"
#include "Pixel.h"

#define HEIGHT 1080
#define WIDTH 1920

typedef struct Image{
	Calque* listCalques;
} Image;

void makeImage(Image* img, int width, int height);
void chargerImage(Image* img, char * pathImg, int width, int height);
void saveImage(Image* img, char* savePath);
void printImage(Image* img, SDL_Surface* framebuffer);
void freeImage(Image* img);

#endif
