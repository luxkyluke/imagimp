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
	return id;
}

void appliqueLUTCalqueByIds(Image* img, int calque_id, int lut_id) {
	if (!img)
		return;
	Calque* c = copyCalque(getCalqueById(img->listCalques, calque_id));
	appliquerLUTById(c, lut_id);
	freeCalque(img->calque_resultat);
	img->calque_resultat = c;
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

int addLUTCalqueById(Image* img, int id, LutOption lut, int val) {
	if (!img)
		return 0;
	Calque* c = getCalqueById(img->listCalques, id);
	return addLUTCalque(c, lut, val);
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
	if(img->calque_resultat)
		freeCalque_r(img->calque_resultat);
}

void fusionnerAllCalques(Image* img){
	fusionCalqueDefinitive(&img->listCalques);
}

void saveImage(Image* img, char* savePath) {
	saveCalque(img->listCalques, savePath);
}

void saveCalqueById(Image *img, int id, char* savePath) {
	if (!img)
		return ;
	Calque* c = getCalqueById(img->listCalques, id);
	saveCalque(c, savePath);
}

void fusionnerCalquesImage(Image* img) {
	if (!img)
		return;
//	img->calque_resultat = fusionnerCalque(img->listCalques);
	if(img->calque_resultat)
		freeCalque(img->calque_resultat);
	img->calque_resultat = fusionnerCalque(img->listCalques);
	//printf("%d, %d, %d\n", img->calque_resultat->pixels[50][50].r, img->calque_resultat->pixels[50][50].g, img->calque_resultat->pixels[50][50].b);
}

void afficheCalqueById(Image* img, int calque_id) {
	Calque* calque = getCalqueById(img->listCalques, calque_id);
	if(calque==NULL)
		return;
	printf("L'id du calque %d\n",calque->id);
	if(img->calque_resultat)
		freeCalque(img->calque_resultat);
	img->calque_resultat = appliquerAllLUT(calque);

}
