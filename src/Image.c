#include "Image.h"




void chargerImage(Image* img, char * pathImg, int width, int height){
	char *rgb = PPM_lire(pathImg, width, height);
	if(rgb == NULL)
		return;
	img->listCalques = makeCalque(width, height, additive);

	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			int r = (int) rgb[3*j*i];
			int g = (int) rgb[3*j*i+1];
			int b = (int) rgb[3*j*i+2];
			Pixel tmp = makePixel(r, g, b, 1);
			img->listCalques->pixels[i][j] = tmp;
		}
	}
	addCalque(img->listCalques);
}

void printImage(Image* img, SDL_Surface* framebuffer){
	if(!img || !img->listCalques){
		printf("Impossible d'afficher ! Image vide ou NULL\n");
		return ;
	}
	int i, j;
	Calque* c = img->listCalques;
	fusionnerCalque(c);
	for (i = 0; i < c->width; i++) {
		for (j = 0; j < c->height; j++) {
			int r = c->pixels[i][j].r;
			int g = c->pixels[i][j].g;
			int b = c->pixels[i][j].b;
			Uint32  color = SDL_MapRGB(framebuffer->format, r, g, b);
			//Uint32  color = SDL_MapRGB(framebuffer->format, 0, 0, 0);
			PutPixel(framebuffer, i, j, color);
		}
	}
}
