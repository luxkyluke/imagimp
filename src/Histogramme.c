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


void calculRedHistogramme(int* red, Calque *c) {
    unsigned int i = 0, j = 0;

    for (i = 0; i < 256; ++i){
        red[i] = 0;
    }

    for (i = 0; i < c->height; i++){
        for (j = 0; j < c->width; j++){
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
        for (j = 0; j < c->width; j++){
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
        for (j = 0; j < c->width; j++){
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

void drawHistogramme(Histogramme* histogramme) {
    int max = 0, i = 0;
    for (i = 0; i < 256; i++){
        // printf("%d %d %d\n",histogramme->valeursBlue[i],histogramme->valeursGreen[i],histogramme->valeursRed[i] );
        if(histogramme->valeursBlue[i] > max)
            max = histogramme->valeursBlue[i];
        if(histogramme->valeursRed[i] > max)
            max = histogramme->valeursRed[i];
        if(histogramme->valeursGreen[i] > max)
            max = histogramme->valeursGreen[i];
    }


    // glPushMatrix();
        // glTranslatef(200,200,0);
    //     // for (i = 0; i < 255; i++){
    //         glColor4f(1.,0,0,0.5);
            // glBegin(GL_LINES);
    //             glVertex3f(i,0,0);
    //             glVertex3f(i,((float)histogramme->valeursRed[i]/(float)max)*100,0);
    //         glEnd();
        // }
    // glPopMatrix();
}









