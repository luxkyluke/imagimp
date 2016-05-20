#include "Calque.h"
#define DEFAULT_FUSION 2

Calque* makeCalque(int w, int h) {
	Calque* list = malloc(sizeof(Calque));
	list->next = NULL;
	list->prev = NULL;
	list->height = h;
	list->width = w;
	list->fusion = DEFAULT_FUSION;
	list->alpha = 0;
	list->listLuts = NULL; // changer les noms des variables des struct
	list->pixels = (Pixel **) malloc(w*sizeof(Pixel*));
	int i, j;
	for (i = 0; i < w; i++){
		list->pixels[i] = (Pixel *) malloc(h*sizeof(Pixel));
		for (j = 0; j < h; j++)
			list->pixels[i][j] = makePixel(255, 255, 255, 1);
	}
	return list;
}

Calque* getNextCalque(Calque* c) {
	if (!c)
		return NULL;
	if (!c->next)
		return c;
	return c->next;
}

Calque* getPrevCalque(Calque* c) {
	if (!c)
		return NULL;
	if (!c->prev)
		return c;
	return c->prev;
}

void setCalqueAlpha(Calque* c, float alpha) {
	c->alpha = alpha;
}

void setFusion(Calque* c, Fusion fusion) {
	c->fusion = fusion;
}

bool calqueIsEmpty(Calque* c) {
	if (!c)
		return false;
	return (c->listLuts == NULL);
}

void addCalque(Calque* c) {
	if (c == NULL)
		return;
	if (calqueIsEmpty(c)) {
		c->listLuts = initLUT();
		return;
	}
	Calque* tmp = c;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	Calque* newCalque = makeCalque(c->width, c->height);
	newCalque->prev = tmp;
	tmp->next = newCalque;
	newCalque->listLuts = initLUT();
}

void removeCalque(Calque* c) {
	if (!c || calqueIsEmpty(c))
		return;
	Calque* tmp = c;
	if (NULL == tmp->next) {
		free(tmp->listLuts);
		return;
	}
	while (NULL != tmp->next->next) {
		tmp = tmp->next;
	}
	free(tmp->next);
	tmp->next = NULL;
}

void chargerImageCalque(Calque* c, char * pathImg, int width, int height){
	char *rgb = PPM_lire(pathImg, width, height);
	if(rgb == NULL){
		perror("Impossible de charger l'image\n");
		return;
	}
	addCalque(c);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int g = (int) rgb[c->width*3*i + j*3];
			int b = (int) rgb[c->width*3*i + j*3 + 1];
			int r = (int) rgb[c->width*3*i + j*3 + 2];
			Pixel tmp = makePixel(r, g, b, 1);
			c->pixels[j][i] = tmp;
		}
	}
	printf("%d\n", r);
}

//Pixel getPixelFusionMult(Calque* c, int i, int j){
//	if(c->next == NULL){
//		return multiPixelFloat(multiPixelFloat(c->pixels[i][j],  c->alpha), c->pixels[i][j].alpha);
//	}
//	return addPixel(c->pixels[i][j], multiPixelFloat(getPixelFusionMult(c->next, i, j), (1. - c->alpha)));
//}
//
//Pixel getPixelFusionAdd(Calque* c, int i, int j){
//	if(c->next == NULL){
//		return multiPixelFloat(multiPixelFloat(c->pixels[i][j],  c->alpha), c->pixels[i][j].alpha);
//	}
//	return addPixel(c->pixels[i][j], getPixelFusionAdd(c->next, i, j));
//}

void fusionnerCalque(Calque* c) {
	if(c == NULL)
		return;
	Calque* calque_resultat = c; // pas aussi simple que �a, il faut faire un for (dixit Anfray)
	Calque* calque_tmp = c->next;// pas aussi simple que �a, il faut faire un for (dixit Anfray)
	while (calque_tmp != NULL && calque_tmp != c) {
		int i, j;
		for (i=0; i < c->height ; i++) {
			for (j=0; j < c->width ; j++) {
				calque_resultat->pixels[i][j].r += calque_tmp->alpha * calque_tmp->pixels[i][j].r
											* calque_tmp->pixels[i][j].alpha;
				calque_resultat->pixels[i][j].g += calque_tmp->alpha * calque_tmp->pixels[i][j].g
											* calque_tmp->pixels[i][j].alpha;
				calque_resultat->pixels[i][j].b += calque_tmp->alpha * calque_tmp->pixels[i][j].b
											* calque_tmp->pixels[i][j].alpha;
			}
		}
		calque_tmp = calque_tmp->next;
	}
}

void appliquerLUT(LUT* L, Calque* calque){
	int i, j;
	for(i=0; i<calque->height; i++){
		for(j=0; i<calque->width; j++){
			calque->pixels[i][j].r = L->lut[calque->pixels[i][j].r];
			calque->pixels[i][j].g = L->lut[calque->pixels[i][j].g];
			calque->pixels[i][j].b = L->lut[calque->pixels[i][j].b];
		}
	}
}

void saveCalque(Calque* c, char * pathImg){
		unsigned char *rgb = malloc(width*height*3 * sizeof(unsigned char));
		int i, j;
		for (i = 0; i < c->height; i++) {
			for (j = 0; j < c->width; j++) {
				rgb[c->width*3*i + j*3] = atoi(c->pixels[j][i].g);
				rgb[c->width*3*i + j*3 + 1]= atoi(c->pixels[j][i].b);
				rgb[c->width*3*i + j*3 + 2] = atoi(c->pixels[j][i].r);
			}
		}
		PPM_ecrire(pathImg, rgb, c->width, c->height)
}
