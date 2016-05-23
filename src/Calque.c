#include "Calque.h"
#define DEFAULT_FUSION 2

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static unsigned int indice_courant = 1;

void remplirCalqueCouleur(Calque* calque, Pixel p) {
	if (!calque)
		return;
	int i, j;
	for (i = 0; i < calque->width; i++) {
		for (j = 0; j < calque->height; j++)
			calque->pixels[i][j] = p;
	}
}

Calque* makeCalque(int w, int h, float op) {
	Calque* calque = malloc(sizeof(Calque));
	if(!calque){
		fprintf(stderr, "Probleme Allocation Calque\n");
		return NULL;
	}
	calque->next = NULL;
	calque->prev = NULL;
	calque->height = h;
	calque->width = w;
	calque->fusion = DEFAULT_FUSION;
	calque->alpha = op;
	calque->listLuts = NULL; // changer les noms des variables des struct
	calque->id = indice_courant++;
	calque->listLuts = makeLUT();
	calque->pixels = (Pixel **) malloc(calque->width * sizeof(Pixel*));
	int i;
	for (i = 0; i < calque->width; i++) {
		calque->pixels[i] = (Pixel *) malloc(calque->height * sizeof(Pixel));
	}
	remplirCalqueCouleur(calque, makePixel(255, 255, 255));

	calque->histogramme = makeHistogramme();
	return calque;
}

Calque* getCalqueById(Calque* c, int id) {
	if (!c)
		return NULL;
	Calque *tmp = c;
	while (tmp != NULL) {
		if (tmp->id == id)
			return tmp;
		tmp = tmp->next;
	}
	fprintf(stderr, "Indice du calque introuvable\n");
	fflush(stdin);
	return NULL;
}

Calque* copyCalque(Calque *c){
	Calque *copie = makeCalque(c->width, c->height, c->alpha);
	int i, j;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			copie->pixels[j][i] = makePixel(c->pixels[j][i].r,
					c->pixels[j][i].g, c->pixels[j][i].b);
		}
	}
	copie->listLuts = c->listLuts;
	return copie;
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

Calque* addNewCalque(Calque* c, float op) {
	if (c == NULL)
		return 0;

	Calque* newCalque = makeCalque(c->width, c->height, op);
	addCalque(c, newCalque);
	return newCalque;
}

void addCalque(Calque* c, Calque* c2){
	if(!c)
		return;
	Calque* last = c;

	while (last->next != NULL) {
		last = last->next;
	}
	c2->prev = last;
	last->next = c2;
}

int addLUTCalque(Calque *c, LutOption lut, int val) {
	if (!c)
		return 0;

	LUT l;
	switch(lut){
		case invert :
			INVERT(&l);
			break;
		case addlum:
			ADDLUM(&l, val);
			break;
		case dimlum:
			DIMLUM(&l, val);
			break;
		case addcon:
			ADDCON(&l, val);
			break;
		case dimcon:
			DIMCON(&l, val);
			break;
	}
	if(!c->listLuts)
		c->listLuts = makeLUT();
	return addLUT(c->listLuts, l.lut);
}

void removeCalque(Calque* c) {
	if (!c)
		return;
	if(c->prev != NULL){
		c->prev->next = c->next;
		c->next = NULL;
	}
	if(c->next != NULL){
		c->next->prev = c->prev;
		c->prev = NULL;
	}
	freeCalque(c);
	c = NULL;
}

int chargerImageCalque(Calque* c, char * pathImg, int width, int height,
		float op) {
	unsigned char *rgb = PPM_lire(pathImg, &width, &height);
	if (rgb == NULL) {
		perror("Impossible de charger l'image\n");
		return 0;
	}
	Calque* calque_tmp = addNewCalque(c, op);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			unsigned int r = (unsigned int) rgb[c->width * 3 * i + j * 3];
			unsigned int g = (unsigned int) rgb[c->width * 3 * i + j * 3 + 1];
			unsigned int b = (unsigned int) rgb[c->width * 3 * i + j * 3 + 2];
			Pixel tmp = makePixel(r, g, b);
			calque_tmp->pixels[j][i] = tmp;
		}
	}
	return calque_tmp->id;
	//calculHistogramme(c->next);
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

void fusionCalqueDefinitive(Calque **calque){
	Calque *next = (*calque)->next;
	*calque = fusionnerCalque(*calque);
	freeCalque_r(next);
}

Calque* fusionnerCalque(Calque* c) {
	if (c == NULL )
		return NULL;
	Calque* test = makeCalque(c->width, c->height, 1.);
	remplirCalqueCouleur(test, makePixel(0, 0, 0));
	Calque *calque_tmp = c->next;
	while (calque_tmp != NULL) {
//		test->listLuts=fusionnerLut(calque_tmp->listLuts);
		//printf("%d, %d, %d\n", test->pixels[50][50].r, test->pixels[50][50].g, test->pixels[50][50].b);
		printf("%d, %d, %d\n", calque_tmp->pixels[50][50].r, calque_tmp->pixels[50][50].g, calque_tmp->pixels[50][50].b);
		int i, j;
		for (i = 0; i < c->height; i++) {
			for (j = 0; j < c->width; j++) {
				//printf("%d, %d, %d\n", test->pixels[450][250].r, test->pixels[450][250].g, test->pixels[450][250].b);
				//printf("%d, %d, %d\n", calque_tmp->pixels[j][i].r, calque_tmp->pixels[j][i].g, calque_tmp->pixels[j][i].b);
				test->pixels[j][i].r = test->pixels[j][i].r*(1.-calque_tmp->alpha) +
						calque_tmp->pixels[j][i].r * calque_tmp->alpha;
				test->pixels[j][i].g = test->pixels[j][i].r*(1.-calque_tmp->alpha) +
						calque_tmp->alpha* calque_tmp->pixels[j][i].g;
				test->pixels[j][i].b = test->pixels[j][i].r*(1.-calque_tmp->alpha) +
						calque_tmp->alpha * calque_tmp->pixels[j][i].b;
				//printf("%d, %d, %d\n", calque_tmp->pixels[j][i].r, calque_tmp->pixels[j][i].g, calque_tmp->pixels[j][i].b);
			}
		}
		calque_tmp = calque_tmp->next;
	}
	calculHistogramme(test);
	return test;
}

void appliqueLUT(Calque* calque, LUT* L) {
	if (!calque || !L)
		return;
	int i, j;
	for (i = 0; i < calque->height; i++) {
		for (j = 0; j < calque->width; j++) {
			calque->pixels[j][i].r = L->lut[calque->pixels[j][i].r];
			calque->pixels[j][i].g = L->lut[calque->pixels[j][i].g];
			calque->pixels[j][i].b = L->lut[calque->pixels[j][i].b];
		}
	}
}

void appliquerLUTById(Calque* calque, int id) {
	if (!calque)
		return;
	LUT* l = getLUTById(calque->listLuts, id);
	appliqueLUT(calque, l);
}

void appliquerAllLUT(Calque* calque) {
	if (!calque) {
		return;
	}
	//fusionnerLut(calque->listLuts);
	appliqueLUT(calque, calque->listLuts);
}

void freeCalque(Calque* c) {
	int i;
	if(c->pixels){
		for (i = 0; i < c->width; i++) {
			free(c->pixels[i]);
		}
		free(c->pixels);
		c->pixels = NULL;
	}
	freeLUT(c->listLuts);
	c->listLuts = NULL;
	printf("FreeCalque OK\n");
}

//void freeCalque_r(Calque* c) {
//	Calque *next, *tmp = c;
//	while(c != NULL){
//		next = c->next;
//		freeCalque(tmp);
//		tmp = next;
//	}
//}

void freeCalque_r(Calque* c) {
	if (c == NULL) {
		return;
	}
	freeCalque_r(c->next);
	freeCalque(c);
	c = NULL;
}

void drawCalqueHistogramme(Calque* c) {
	drawHistogramme(c->histogramme);
}

void saveCalque(Calque* c, char *pathImg) {
	if(!c)
		return;
	c=fusionnerCalque(c);
//	printf("%d, %d, %d\n", c->pixels[50][50].r, c->pixels[50][50].g, c->pixels[50][50].b);
//	fflush(stdin);
	unsigned char *rgb = malloc(
			c->width * c->height * 3 * sizeof(unsigned char));
	int i, j;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			rgb[c->width * 3 * i + j * 3] = c->pixels[j][i].r;
			rgb[c->width * 3 * i + j * 3 + 1] = c->pixels[j][i].g;
			rgb[c->width * 3 * i + j * 3 + 2] = c->pixels[j][i].b;
		}
	}
	PPM_ecrire(pathImg, rgb, c->width, c->height);
	printf("Sauvegarde Calque %d OK\n", c->id);
}

void drawCalque(Calque *c) {
	int i, j;
	glPushMatrix();
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			int r = c->pixels[j][i].r;
			int g = c->pixels[j][i].g;
			int b = c->pixels[j][i].b;
			//Uint32  color = SDL_MapRGB(framebuffer->format, r, g, b);
			//Uint32  color = SDL_MapRGB(framebuffer->format, 0, 0, 0);
			// PutPixel(framebuffer, j, i, color);

			glBegin(GL_POINTS);
			glColor3f(r / 255., g / 255., b / 255.);
			if(c->width>WINDOW_WIDTH || c->height>WINDOW_HEIGHT)
				glVertex2f(j*WINDOW_WIDTH/c->width, i*WINDOW_HEIGHT/c->height);
			else
				glVertex2f(j, i);
			glEnd();

		}
	}
	glPopMatrix();
}

