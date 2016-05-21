#include "IHM.h"
#include "glut_tools.h"
#include "Geometry.h"

void DessinButton(char *text) {
    glScalef(190,40,1);
    glColor3f(1,1,0);
    dessinCarre(1,ColorRGB(1,1,1));

    glPushMatrix();
    glScalef(1,1,1);
    glTranslatef(0.15, 0.6, 0);
    glColor3f(0, 0, 0);
    vBitmapOutput(0, 0, text, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();
}

void dessinIHM(Calque* c) {
    char luminosite[] = "Luminosite", contraste[] = "Contraste", saturation[] = "Saturation", calque[] = "Nouveau calque", image[] = "Charger image";

    // Luminosité.
    glPushMatrix();
    glTranslatef(50, 160, 0);
    glColor3f(149./255., 165./255., 166./255.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glEnd();
    glTranslatef(90,0,0);
    glColor3f(1,1,1);
    glScalef(20,20,0);
    dessinCercle(10,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, 160, 0);
    glColor3d(1, 1, 1);
    vBitmapOutput(-2, 45, luminosite, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();


    // Contraste.
    glPushMatrix();
    glTranslatef(50, 260, 0);
    glColor3f(149./255., 165./255., 166./255.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glEnd();
    glTranslatef(90,0,0);
    glColor3f(1,1,1);
    glScalef(20,20,0);
    dessinCercle(10,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, 260, 0);
    glColor3d(1, 1, 1);
    vBitmapOutput(-2, 45, contraste, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();

    // Contraste.
    glPushMatrix();
    glTranslatef(50, 360, 0);
    glColor3f(149./255., 165./255., 166./255.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glEnd();
    glTranslatef(90,0,0);
    glColor3f(1,1,1);
    glScalef(20,20,0);
    dessinCercle(10,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, 360, 0);
    glColor3d(1, 1, 1);
    vBitmapOutput(-2, 45, saturation, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55, 460,0);
    DessinButton(calque);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55, 520,0);
    DessinButton(image);
    glPopMatrix();


}
