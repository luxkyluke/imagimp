#include "Calque.h"

Calque* makeCalque(int h, int w) {
	Calque* list = malloc(sizeof(Calque));
	list->next = NULL;
	list->prev = NULL;
	list->height = h;
	list->width = w;
	list->fusion = 0;
	list->alpha = 0;
	list->listLuts = NULL; // changer les noms des variables des struct
	int i, j;
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++) // h et w : variables globales
			list->pixels[i][j] = createPixel(255, 255, 255, 1);

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
	if (NULL == c)
		return;
	if (isListCalquesEmpty(c)) {
		c->listLuts = initListLuts();
		return;
	}
	Calque* tmp = c;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	Calque* newCalque = makeCalque(c->height, c->width);
	newCalque->prev = tmp;
	tmp->next = newCalque;
	newCalque->listLuts = initListLuts();
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

Pixel getPixelFusionAdd(Calque* c, int i, int j){
	if(c == NULL)
		return ;
	if(c->next == NULL){
		return multiPixel(multiPixelFloat(c->pixels[i][j],  c->alpha), c->pixels[i][j].alpha));
	}
	return addPixel(c->pixels[i][j], getPixelFusionAdd(c->next, i, j));
}

void fusionnerCalque(Calque* c) {
	int i, j;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			c->pixels[i][j] = getPixelFusionAdd(c, i, j);
		}
	}

//	Calque* calque_resultat = c; // pas aussi simple que ça, il faut faire un for (dixit Anfray)
//	Calque* calque_tmp = calque_tmp->next;// pas aussi simple que ça, il faut faire un for (dixit Anfray)
//	while (calque_tmp != NULL) {
//		int i, j;
//		for (i=0; i < c->height ; i++) {
//			for (j=0; j < c->width ; j++) {
//				calque_resultat->pixels[i][j].r += calque_tmp->alpha * calque_tmp->pixels[i][j].r
//											* calque_tmp->pixels[i][j].alpha;
//				calque_resultat->pixels[i][j].g += calque_tmp->alpha * calque_tmp->pixels[i][j].g
//											* calque_tmp->pixels[i][j].alpha;
//				calque_resultat->pixels[i][j].b += calque_tmp->alpha * calque_tmp->pixels[i][j].b
//											* calque_tmp->pixels[i][j].alpha;
//			}
//		}
//		calque_tmp = calque_tmp->next;
//	}
}
