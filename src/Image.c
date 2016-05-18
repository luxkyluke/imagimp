#include "Image.h"
#include <math.h>

void makeImage(Image* img, int width, int height){
	img->listCalques = makeCalque(width, height);
}

void chargerImage(Image* img, char * pathImg, int width, int height){
	chargerImageCalque(img->listCalques, pathImg, width, height);
}

void printImage(Image* img, SDL_Surface* framebuffer){
	if(!img || !img->listCalques){
		printf("Impossible d'afficher ! Image vide ou NULL\n");
		return ;
	}
	int i, j;
	Calque* c = img->listCalques;
	fusionnerCalque(c);

	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			int r = c->pixels[j][i].r;
			int g = c->pixels[j][i].g;
			int b = c->pixels[j][i].b;
			Uint32  color = SDL_MapRGB(framebuffer->format, r, g, b);
			//Uint32  color = SDL_MapRGB(framebuffer->format, 0, 0, 0);
			PutPixel(framebuffer, j, i, color);
		}
	}
}
