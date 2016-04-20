#include "Image.h"


#define HEIGHT 1080
#define WIDTH 1920

void chargerImage(Image* img,char * pathImg){
	//img->listCalques
}

void printImage(Image* img, SDL_Surface* framebuffer){
	int i, j;
	Calque* c = img->listCalques;
	fusionnerCalque(c);
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			Uint32  color = SDL_MapRGB(framebuffer->format, c->pixels[i][j].r, c->pixels[i][j].g, c->pixels[i][j].b);
			PutPixel(framebuffer, i, j, color);
		}
	}
}
