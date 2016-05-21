#include "Image.h"
//#include "Histogramme.h"

Image* makeImage(int width, int height) {
	Image* img = (Image*) malloc(sizeof(Image));
	img->listCalques = makeCalque(width, height, 0.);
	img->calque_resultat = NULL;
	return img;
}

void chargerImage(Image* img, char * pathImg, int width, int height, float op) {
	chargerImageCalque(img->listCalques, pathImg, width, height, op);
	updateImage(img);
}

void appliqueLUTCalqueId(Image* img, int id, LUT* lut) {
	if (LUTIsEmpty(lut) || !img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	appliquerLUT(lut, c);
	updateImage(img);
}

void drawImageHistogramme(Image* img) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
	if (!img->calque_resultat)
		updateImage(img);

	drawCalqueHistogramme(img->calque_resultat);
}

void printImage(Image* img, SDL_Surface* framebuffer) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
	if (!img->calque_resultat)
		updateImage(img);

	drawCalque(img->calque_resultat);
}

void freeImage(Image* img) {
	freeCalque_r(img->listCalques);
}

void updateImage(Image* img) {
	if(!img)
		return;
	img->calque_resultat = fusionnerCalque(img->listCalques);
}
