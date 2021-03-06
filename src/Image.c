#include "Image.h"
//#include "Histogramme.h"

Image* makeImage(int width, int height) {
	Image* img = (Image*) malloc(sizeof(Image));
	img->listCalques = makeCalque(width, height, 0.);
	img->calque_resultat = NULL;
	return img;
}

int chargerImage(Image* img, const char * pathImg, int width, int height, float op) {
	int id = chargerImageCalque(img->listCalques, pathImg, width, height, op);
	return id;
}

void addEffetCalqueById(Image* img, int id, Effet effet) {
	if (!img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	if (!c)
		return;
	c->effet = effet;
}

void drawImageHistogramme(Image* img) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
	drawCalqueHistogramme(img->calque_resultat);
}

void addLUTCalqueById(Image* img, int id, LutOption lut, int val) {
	if (!img)
		return;
	Calque* c ;
	if(id>1)
		c= getCalqueById(img->listCalques, id);
	else
		c=img->calque_resultat;
	addLUTCalque(c, lut, val);
}

void modifyOppacityCalqueById(Image *img, int id, float alpha){
	Calque* c = getCalqueById(img->listCalques, id);
	c->alpha = alpha;
}

void drawImage(Image* img, SDL_Surface* framebuffer) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
	drawCalque(img->calque_resultat);
}

void freeImage(Image* img) {
	freeCalque_r(img->listCalques);
	if (img->calque_resultat)
		freeCalque(img->calque_resultat);
}

void saveImage(Image* img, char* savePath) {
	saveCalque(img->listCalques, savePath);
}


void fusionnerCalquesImage(Image* img) {
	if (!img)
		return;
	Calque **c = &( img->calque_resultat);
	bool effectToResult =false;
	if (*c != NULL){
		if((*c)->effet != none || ((*c)->listLuts != NULL && !LUTIsEmpty((*c)->listLuts)))
			effectToResult = true;
		else
			freeCalque(img->calque_resultat);
	}
	if(effectToResult){
		(*c) = appliquerEffet(*c);
		(*c) = appliquerAllLUT(*c);
		calculHistogramme(*c);
	}
	else{
		(*c) = fusionnerCalque(img->listCalques);
	}

}

void resetOpacityCalqueById(Image* img, int id){
	Calque *c = getCalqueById(img->listCalques, id);
	c->alpha = 1.;
}

void switchEffectById(Image * img, int id, Effet effet){
	Calque *c;
	if(id >1)
		c= getCalqueById(img->listCalques, id);
	else
		c = img->calque_resultat;
	if(isOnEffect(c))
		resetEffet(c);
	else
		c->effet = effet;
}

void afficheCalqueById(Image* img, int calque_id) {
	Calque* calque = getCalqueById(img->listCalques, calque_id);

	if (calque == NULL)
		return;
	if (img->calque_resultat)
		freeCalque(img->calque_resultat);
	img->calque_resultat = appliquerAllLUT(calque);
	if (calque->effet != none) {
		img->calque_resultat->effet = calque->effet;
		img->calque_resultat = appliquerEffet(img->calque_resultat);
	}

	calculHistogramme(img->calque_resultat);
}

void removeClaqueById(Image* img, int id) {
	if (!img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	if (c)
		removeCalque(c);
}
