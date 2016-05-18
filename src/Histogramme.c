#include "Histogramme.h"
#include "Calque.h"

void calculRedHistogramme(int* red, Calque *c) {
    unsigned int i = 0, j = 0;

    for (i = 0; i < 256; ++i){
        red[i] = 0;
    }

    for (i = 0; i < c->height; i++){
        for (j = 2; j < c->width; j++){
            red[c->pixels[j][i].b]+=1;
        }
    }
}

void calculGreenHistogramme(int* green, Calque *c) {
    unsigned int i = 0, j = 0;

    for (i = 0; i < 256; ++i){
        green[i] = 0;
    }

    for (i = 0; i < c->height; i++){
        for (j = 2; j < c->width; j++){
            green[c->pixels[j][i].b]+=1;
        }
    }
}

void calculBlueHistogramme(int* blue, Calque *c) {
    unsigned int i = 0, j = 0;

    for (i = 0; i < 256; ++i){
        blue[i] = 0;
    }

    for (i = 0; i < c->height; i++){
        for (j = 2; j < c->width; j++){
            blue[c->pixels[j][i].b]+=1;
        }
    }
}

void calculLuminositeHistogramme(int* luminosite, Calque *c) {
    unsigned int i = 0;

    for (i = 0; i < 256; ++i){
        luminosite[i] = 0;
    }

    for (i = 0; i < 256; ++i){
        luminosite[i] = (c->histogramme->valeursBlue[i] + c->histogramme->valeursRed[i] + c->histogramme->valeursGreen[i])/3;
    }
}


void calculHistogramme(Calque *c) {
    if(c!=NULL || c->histogramme!=NULL) {
        calculBlueHistogramme(c->histogramme->valeursBlue, c);
        calculRedHistogramme(c->histogramme->valeursRed, c);
        calculGreenHistogramme(c->histogramme->valeursGreen, c);
        calculLuminositeHistogramme(c->histogramme->valeursLuminosite, c);
    }
}
