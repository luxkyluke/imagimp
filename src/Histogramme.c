#include "Histogramme.h"
#include "Calque.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <SDL/SDL.h>
#include "Geometry.h"

#define TAILLE_TAB 256

void initTab(int* tab) {
	int i;
	for (i = 0; i < TAILLE_TAB; ++i) {
		tab[i] = 0;
	}
}

Histogramme* makeHistogramme() {
	Histogramme *h = (Histogramme*) malloc(sizeof(Histogramme));
	h->valeurMax = 1;
	initTab(h->valeursBlue);
	initTab(h->valeursRed);
	initTab(h->valeursGreen);
	return h;
}

void calculRedHistogramme(int* red, Calque *c) {
	unsigned int i = 0, j = 0;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			red[c->pixels[j][i].r] += 1;
		}
	}
}

void calculGreenHistogramme(int* green, Calque *c) {
	unsigned int i = 0, j = 0;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			green[c->pixels[j][i].g] += 1;
		}
	}
}

void calculBlueHistogramme(int* bleu, Calque *c) {
	unsigned int i = 0, j = 0;
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			bleu[c->pixels[j][i].b] += 1;
		}
	}
}

void calculLuminositeHistogramme(int* luminosite, Calque *c) {
	unsigned int i = 0;
	for (i = 0; i < TAILLE_TAB; ++i) {
		luminosite[i] = (c->histogramme->valeursBlue[i]
				+ c->histogramme->valeursRed[i]
				+ c->histogramme->valeursGreen[i]) / 3;
	}
}

int calculMaxTab(int *tab){
	int i, max=1;
	for (i = 0; i < TAILLE_TAB; i++) {
		if (tab[i] > max)
			max = tab[i];
	}
	return max;
}

void calculHistogramme(Calque *c) {
	if (c != NULL || c->histogramme != NULL) {
		calculBlueHistogramme(c->histogramme->valeursBlue, c);
		calculRedHistogramme(c->histogramme->valeursRed, c);
		calculGreenHistogramme(c->histogramme->valeursGreen, c);
		calculLuminositeHistogramme(c->histogramme->valeursLuminosite, c);
		c->histogramme->valeurMaxBlue = calculMaxTab(c->histogramme->valeursBlue);
		c->histogramme->valeurMaxRed = calculMaxTab(c->histogramme->valeursRed);
		c->histogramme->valeurMaxGreen = calculMaxTab(c->histogramme->valeursGreen);
		if( c->histogramme->valeurMaxBlue > c->histogramme->valeurMax)
				c->histogramme->valeurMax = c->histogramme->valeurMaxBlue;
		if( c->histogramme->valeurMaxRed > c->histogramme->valeurMax)
				c->histogramme->valeurMax = c->histogramme->valeurMaxRed;
		if( c->histogramme->valeurMaxGreen > c->histogramme->valeurMax)
				c->histogramme->valeurMax = c->histogramme->valeurMaxGreen;
	}
}

void drawHistogramme(Histogramme* histogramme) {
	int max = 0, i = 0;


	glPushMatrix();
	//glTranslatef(200,200,0);
	for (i = 0; i < TAILLE_TAB; i++) {
		glColor3f(1., 0, 0.);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(i, 0, 0);
		glVertex3f(i, ((float) histogramme->valeursRed[i] / (float) max) * 100,
				0);
		glEnd();
	}
	glPopMatrix();
}

void printTab(int *tab, float max) {
	int i;
	float j, res;
	for (i = 0; i < TAILLE_TAB; i++) {
		printf("%9d%15d       ", i, tab[i]);
		res = tab[i] / max;
		res = res * 100;
		for (j = 0; j < res; j++)
			printf("*");
		printf("\n");
	}
}

void printHistogramme(Histogramme* h) {
	printf("\n\n*********PIXELS ROUGES*********\n\n");
	printTab(h->valeursRed, (float)h->valeurMax);

	printf("\n\n*********PIXELS VERTS*********\n\n");
	printTab(h->valeursGreen, (float)h->valeurMax);

	printf("\n\n*********PIXELS BLEUS*********\n\n");
	printTab(h->valeursBlue, (float)h->valeurMax);

	printf("\n\n*********PIXELS BLEUS*********\n\n");
	printTab(h->valeursLuminosite, (float)h->valeurMax);
}

