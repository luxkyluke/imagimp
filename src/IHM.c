#include "IHM.h"
#include "glut_tools.h"
#include "Geometry.h"

#define WIDTH_SLIDER 200

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

void dessinIHM(Calque* c, int xLuminosite, int xContraste, int xSaturation) {
    // printf("%d xLuminosite\n", xLuminosite);
    float valueSliderLuminosite = -xLuminosite;
    float valueSliderContraste= -xContraste;
    char luminosite[] = "Luminosite", contraste[] = "Contraste", saturation[] = "Saturation", calque[] = "Nouveau calque", image[] = "Charger image";

    // Luminosité.
    glPushMatrix();
    glTranslatef(50, 160, 0);
    glColor3f(149./255., 165./255., 166./255.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(WIDTH_SLIDER, 0, 0);
    glEnd();
    glTranslatef(100 - xLuminosite ,0,0);
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
    glTranslatef(100 - xContraste,0,0);
    glColor3f(1,1,1);
    glScalef(20,20,0);
    dessinCercle(10,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, 260, 0);
    glColor3d(1, 1, 1);
    vBitmapOutput(-2, 45, contraste, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();

    // Saturation.
    glPushMatrix();
    glTranslatef(50, 360, 0);
    glColor3f(149./255., 165./255., 166./255.);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 0, 0);
    glEnd();
    glTranslatef(100 - xSaturation,0,0);
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

int isOnLuminosite(int posX, int posY, int xLuminosite) {
    if(posX >= 931 - xLuminosite && posX <= 950 - xLuminosite && posY>=151 && posY <= 172)
        return 1;
    else
        return 0;
}

int isOnContraste(int posX, int posY, int xContraste) {
    if(posX >= 931 - xContraste && posX <= 950 - xContraste && posY>=250 && posY <= 270)
        return 1;
    else
        return 0;
}

int isOnSaturation(int posX, int posY, int xSaturation) {
    if(posX >= 931 - xSaturation && posX <= 950 - xSaturation && posY>=350 && posY <= 370)
        return 1;
    else
        return 0;
}

int isOnChargerImage(int posX, int posY) {
   if(posX >= 855 && posX <= 1045 && posY>=520 && posY <= 560)
        return 1;
   else
        return 0;
}

int isOnNouveauCalque(int posX, int posY) {
   if(posX >= 855 && posX <= 1045 && posY>=460 && posY <= 500)
        return 1;
   else
        return 0;
}
