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

void appliqueLUTCalqueByIds(Image* img, int calque_id, int lut_id) {
//	if (!img)
//		return;
//	Calque* c = copyCalque(getCalqueById(img->listCalques, calque_id));
//	if (!c)
//		return;
//	appliquerLUTById(c, lut_id);
//	if (img->calque_resultat)
//		freeCalque(img->calque_resultat);
//	img->calque_resultat = c;
}

void appliqueAllLUTCalqueById(Image* img, int id) {
	if (!img || !img->listCalques)
		return;

	//Calque* c = copyCalque(getCalqueById(img->listCalques, id));
	Calque* c = getCalqueById(img->listCalques, id);
	appliquerAllLUT(c);
	fusionnerCalquesImage(img);
	//img->calque_resultat = c;
//	addCalque(img->calque_resultat, c);

}

void drawImageHistogramme(Image* img) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
	//if (!img->calque_resultat)
	//updateImage(img);

	drawCalqueHistogramme(img->calque_resultat);
}

void addLUTCalqueById(Image* img, int id, LutOption lut, int val) {
	if (!img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	addLUTCalque(c, lut, val);

}

void drawImage(Image* img, SDL_Surface* framebuffer) {
	if (!img || !img->listCalques) {
		printf("Impossible d'afficher l'image ! Image vide ou NULL\n");
		return;
	}
//	if (!img->calque_resultat)
//		updateImage(img);

	drawCalque(img->calque_resultat);
}

void freeImage(Image* img) {
	freeCalque_r(img->listCalques);
	if (img->calque_resultat)
		freeCalque(img->calque_resultat);
}

//void fusionnerAllCalques(Image* img) {
//	fusionCalqueDefinitive(&img->listCalques);
//}

void saveImage(Image* img, char* savePath) {
	saveCalque(img->listCalques, savePath);
}

void saveCalqueById(Image *img, int id, char* savePath) {
	if (!img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	if (c)
		saveCalque(c, savePath);
}

void changeFusionClaqueToAdditive(Image* img, int id) {
	if (!img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	if (c)
		setFusion(c, additive);
}

void fusionnerCalquesImage(Image* img) {
	if (!img)
		return;
	if (img->calque_resultat)
		freeCalque(img->calque_resultat);
	img->calque_resultat = fusionnerCalque(img->listCalques);
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
