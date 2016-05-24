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

void dessinIHM(IHM* ihm) {
    // printf("%d xLuminosite\n", xLuminosite);
    char calque[] = "Nouveau calque", image[] = "Charger image";

    drawSlider(ihm->sliderLuminosite);
    drawSlider(ihm->sliderContraste);
    drawSlider(ihm->sliderSaturation);
    drawSlider(ihm->sliderOpacite);

    glPushMatrix();
    glTranslatef(55, 560,0);
    DessinButton(calque);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55, 620,0);
    DessinButton(image);
    glPopMatrix();
}

int isOnLuminosite(int posX, int posY, int xLuminosite) {
    if(posX >= 931 - xLuminosite && posX <= 950 - xLuminosite && posY>=151 && posY <= 172)
        return 1;
    else
        return 0;
}

int isOnOpacite(int posX, int posY, int xOpacite) {
    if(posX >= 940 - xOpacite && posX <= 960 - xOpacite && posY>=453 && posY <= 468) {
        return 1;
    }
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
   if(posX >= 855 && posX <= 1045 && posY>=620 && posY <= 660)
        return 1;
   else
        return 0;
}

int isOnNouveauCalque(int posX, int posY) {
   if(posX >= 855 && posX <= 1045 && posY>=560 && posY <= 600)
        return 1;
   else
        return 0;
}

Slider* makeSlider(int width, int posY, int posSlider, SliderName name, char* title) {
    Slider* slider = malloc(sizeof(Slider));
    if(!slider){
        fprintf(stderr, "Probleme Allocation Slider\n");
        return NULL;
    }
    slider->width     = width;
    slider->posSlider = posSlider;
    slider->name      = name;
    slider->posY      = posY;
    slider->title     = title;
    slider->startPos     = 100;
    return slider;
}

IHM* makeIHM(int windowWidth, int windowHeight, int paramWidth, int filterHeight) {
    IHM* ihm = (IHM*) malloc(sizeof(IHM));
    if(!ihm){
        fprintf(stderr, "Probleme Allocation IHM\n");
        return NULL;
    }
    ihm->windowWidth  = windowWidth;
    ihm->windowHeight = windowHeight;
    ihm->paramWidth   = paramWidth;
    ihm->filterHeight = filterHeight;
    // 100 est pour que le centre soit centré.
    ihm->sliderLuminosite   = makeSlider(200,160,100,luminosite,"luminosite");
    ihm->sliderContraste    = makeSlider(200,260,100,contraste,"contraste");
    ihm->sliderSaturation   = makeSlider(200,360,100,saturation,"saturation");
    ihm->sliderOpacite      = makeSlider(100,460,100,opacite,"opacite");
    ihm->btnCalque          = makeButton(190,40,25,560,"Nouveau calque",calque);
    ihm->btnImage           = makeButton(190,40,25,620,"Charger image",charger);
    return ihm;
}

void drawSlider(Slider* slider) {
    glPushMatrix();
        glTranslatef(50, slider->posY, 0);
        glColor3f(149./255., 165./255., 166./255.);
        glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(slider->width, 0, 0);
        glEnd();
        // if(slider->name == opacite){
        //     glTranslatef((slider->posSlider+100),0,0);
        // }
        // else
            glTranslatef(slider->posSlider,0,0);
        glColor3f(1,1,1);
        glScalef(20,20,0);
        dessinCercle(10,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, slider->posY, 0);
    glColor3d(1, 1, 1);
    vBitmapOutput(-2, 45, slider->title, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();
}

Button* makeButton(int width, int height, int posX, int posY, char* title, BtnName name) {
    Button* button = malloc(sizeof(Button));
    if(!button){
        fprintf(stderr, "Probleme Allocation Button\n");
        return NULL;
    }
    button->width      = width;
    button->name       = name;
    button->height     = height;
    button->posX       = posX;
    button->title      = title;
    button->isSelected = 0;
    return button;
}
