#include "Image.h"
//#include "Histogramme.h"

Image* makeImage(int width, int height) {
	Image* img = (Image*) malloc(sizeof(Image));
	img->listCalques = makeCalque(width, height, 0.);
	img->calque_resultat = NULL;
	return img;
}

int chargerImage(Image* img, char * pathImg, int width, int height, float op) {
	int id = chargerImageCalque(img->listCalques, pathImg, width, height, op);
	updateImage(img);
	return id;
}

void appliqueLUTCalqueByIds(Image* img, int calque_id, int lut_id) {
	if (!img)
		return;
	Calque* c = copyCalque(getCalqueById(img->listCalques, calque_id));
	appliquerLUTById(c, lut_id);
	img->calque_resultat = c;
}

void appliqueAllLUTCalqueById(Image* img, int id) {
	if (!img)
		return;
	Calque* c = copyCalque(getCalqueById(img->listCalques, id));
	appliquerAllLUT(c);
	img->calque_resultat = c;
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

int addLUTCalqueById(Image* img, int id, LutOption lut, int val){
	if (!img)
			return 0;
	Calque* c = getCalqueById(img->listCalques, id);
	return addLUTCalque(c, lut, val);
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
