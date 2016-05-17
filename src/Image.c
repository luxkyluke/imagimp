#include "Image.h"
#include <math.h>

void chargerImage(Image* img, char * pathImg, int width, int height){
	char *rgb = PPM_lire(pathImg, width, height);
	if(rgb == NULL)
		return;
	img->listCalques = makeCalque(width, height, additive);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int r = (int) rgb[img->listCalques->width*3*i + j*3];
			int g = (int) rgb[img->listCalques->width*3*i + j*3 + 1];
			int b = (int) rgb[img->listCalques->width*3*i + j*3 + 2];
			Pixel tmp = makePixel(r, g, b, 1);
			img->listCalques->pixels[j][i] = tmp;
		}
	}
}

void printImage(Image* img, SDL_Surface* framebuffer){
	if(!img || !img->listCalques){
		printf("Impossible d'afficher ! Image vide ou NULL\n");
		return ;
	}
	int i, j;
	Calque* c = img->listCalques;
	fusionnerCalque(c);

	// printf("c->width: %d, c->eight : %d\n",c->width,c->height);
	printf("%d\n",c->width);
	for (i = 0; i < c->width; i++) {
		for (j = 0; j < c->height; j++) {
			// printf("rouge : %d, vert : %d bleu : %d\n", c->pixels[i][j].r,c->pixels[i][j].g,c->pixels[i][j].b);
			int r = c->pixels[i][j].r;
			int g = c->pixels[i][j].g;
			int b = c->pixels[i][j].b;
			Uint32  color = SDL_MapRGB(framebuffer->format, r, g, b);
			//Uint32  color = SDL_MapRGB(framebuffer->format, 0, 0, 0);
			PutPixel(framebuffer, i, j, color);
		}
	}
}
