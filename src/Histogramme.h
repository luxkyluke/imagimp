#ifndef _HISTOGRAMME_H_
#define _HISTOGRAMME_H_

typedef struct Calque Calque;

typedef struct histogramme{
	int valeursRed[256];
    int valeursGreen[256];
    int valeursBlue[256];
    int valeursLuminosite[256];
}Histogramme;

void calculRedHistogramme(int * red, Calque *c);
void calculGreenHistogramme(int * green, Calque *c);
void calculBlueHistogramme(int * blue, Calque *c);
void calculLuminositeHistogramme(int* luminosite, Calque *c);
void calculHistogramme(Calque *c);

#endif
