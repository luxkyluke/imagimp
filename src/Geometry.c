#include "Geometry.h"
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


int IsZero(float x) {
    return x > -EPSILON && x < EPSILON;
}

void dessinCercle(int n, int fill){
  int i;
  double Pi = 3.14;
  float mycos, mysin;
  if (fill == 0){
    glBegin(GL_LINE_LOOP);
    for (i=0; i<n; i++){
      mycos = cos(i*2*Pi/n)/2;
      mysin = sin(i*2*Pi/n)/2;
      glVertex2f(mycos, mysin);
    }
    glEnd();
  }
  else{
    glBegin(GL_POLYGON);
    for (i=0; i<n; i++){
      mycos = cos(i*2*Pi/n)/2;
      mysin = sin(i*2*Pi/n)/2;
      glVertex2f(mycos, mysin);
    }
  glEnd();
  }
}

void dessinCarre(int fill, Color3f color){
  if (fill == 1){
    glBegin(GL_QUADS);
      glColor3f(color.r,color.g, color.b);
      glVertex2f(0,1); //point de depart
      glVertex2f(1,1); //point d’arrive
      glVertex2f(1,0);
      glVertex2f(0,0);
    glEnd();
  }
  else{
    glBegin(GL_LINE_LOOP);
      glColor3f(color.r,color.g, color.b);
      glVertex2f(-0.5,0.5); //point de depart
      glVertex2f(0.5,0.5); //point d’arrive
      glVertex2f(0.5,-0.5);
      glVertex2f(-0.5,-0.5);
    glEnd();
  }
}
