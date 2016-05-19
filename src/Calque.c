#include "Calque.h"
#define DEFAULT_FUSION 2

static unsigned int indice_courant=0;

Calque* makeCalque(int w, int h) {
	Calque* list = malloc(sizeof(Calque));
	list->next = NULL;
	list->prev = NULL;
	list->height = h;
	list->width = w;
	list->fusion = DEFAULT_FUSION;
	list->alpha = 0;
	list->listLuts = NULL; // changer les noms des variables des struct
	list->ind = indice_courant++;
	list->pixels = (Pixel **) malloc(w*sizeof(Pixel*));
	int i, j;
	for (i = 0; i < w; i++){
		list->pixels[i] = (Pixel *) malloc(h*sizeof(Pixel));
		for (j = 0; j < h; j++)
			list->pixels[i][j] = makePixel(255, 255, 255, 1);
	}

	list->histogramme = malloc(sizeof(Histogramme));
	calculHistogramme(list);
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
		c->listLuts = makeLUT();
		return;
	}
	Calque* tmp = c;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	Calque* newCalque = makeCalque(c->width, c->height);
	newCalque->prev = tmp;
	tmp->next = newCalque;
	newCalque->listLuts = makeLUT();
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
	unsigned char *rgb = PPM_lire(pathImg, &width, &height);
	if(rgb == NULL){
		perror("Impossible de charger l'image\n");
		return;
	}
	addCalque(c);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			unsigned int r = (unsigned int) rgb[c->width*3*i + j*3];
			unsigned int g = (unsigned int) rgb[c->width*3*i + j*3 + 1];
			unsigned int b = (unsigned int) rgb[c->width*3*i + j*3 + 2];
			Pixel tmp = makePixel(r, g, b, 1);
			c->pixels[j][i] = tmp;
		}
	}
	calculHistogramme(c);
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
	Calque* calque_tmp = c->next;
	while (calque_tmp != NULL && calque_tmp != c) {
		int i, j;
		for (i=0; i < c->height ; i++) {
			for (j=0; j < c->width ; j++) {
				c->pixels[j][i].r += calque_tmp->alpha * calque_tmp->pixels[j][i].r
											* calque_tmp->pixels[j][i].alpha;
				c->pixels[j][i].g += calque_tmp->alpha * calque_tmp->pixels[j][i].g
											* calque_tmp->pixels[j][i].alpha;
				c->pixels[j][i].b += calque_tmp->alpha * calque_tmp->pixels[j][i].b
											* calque_tmp->pixels[j][i].alpha;
			}
		}
		calque_tmp = calque_tmp->next;
	}
	suppCalque(c->next);
	c->next = NULL;
}

void appliquerLUT(LUT* L, Calque* calque){
	int i, j;
	fusionnerLut(L);
	for(i=0; i<calque->height; i++){
		for(j=0; j<calque->width; j++){
			calque->pixels[j][i].r = L->lut[calque->pixels[j][i].r];
			calque->pixels[j][i].g = L->lut[calque->pixels[j][i].g];
			calque->pixels[j][i].b = L->lut[calque->pixels[j][i].b];
		}
	}
}

void freeCalque(Calque* c){
	int i;
	for(i=0; i< c->height; i++){
		free(c->pixels[i]);
	}
	free(c->pixels);
	c->pixels = NULL;
	freeLUT(c->listLuts);
	c->listLuts = NULL;
}

void suppCalque(Calque* c){
	if(c == NULL){
		return;
	}
	suppCalque(c->next);
	freeCalque(c);
	c = NULL;
}


