#include "Calque.h"

Calque* makeCalque(int h, int w, Fusion fusion) {
	Calque* list = malloc(sizeof(Calque));
	list->next = NULL;
	list->prev = NULL;
	list->height = h;
	list->width = w;
	list->fusion = fusion;
	list->alpha = 0;
	list->listLuts = NULL; // changer les noms des variables des struct
	list->pixels = (Pixel **) malloc(h*sizeof(Pixel*));
	int i, j;
	for (i = 0; i < h; i++){
		list->pixels[i] = (Pixel *) malloc(w*sizeof(Pixel));
		for (j = 0; j < w; j++)
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
	Calque* newCalque = makeCalque(c->height, c->width, c->fusion);
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

	Calque* calque_resultat = c; // pas aussi simple que ça, il faut faire un for (dixit Anfray)
	Calque* calque_tmp = c->next;// pas aussi simple que ça, il faut faire un for (dixit Anfray)
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
