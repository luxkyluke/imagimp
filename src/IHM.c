#include "IHM.h"
#include "glut_tools.h"
#include "Geometry.h"

#define WIDTH_SLIDER 200

void DessinButton(Button* button) {
    glPushMatrix();
    glTranslatef(button->posX, button->posY,0);
    glScalef(button->width,button->height,1);
    glColor3f(1,1,0);
    dessinCarre(1,ColorRGB(1,1,1));
    glPopMatrix();
    glPushMatrix();
    glTranslatef(button->posX+30, button->posY+button->height/2+5, 0);
    glColor3f(0, 0, 0);
    vBitmapOutput(0, 0, button->title, GLUT_BITMAP_HELVETICA_18);
    glPopMatrix();
}

int isOnLuminosite(int posX, int posY, int xLuminosite) {
    if(posX >= 931 - xLuminosite && posX <= 950 - xLuminosite && posY>=151 && posY <= 172)
        return 1;
    else
        return 0;
}

int isOnOpacite(int posX, int posY, int xOpacite) {
    printf("posXOpac %d, posYOpac %d\n",posX,posY);
    if(posX >= 940 - xOpacite && posX <= 960 - xOpacite && posY>=353 && posY <= 368) {
        printf("in\n");
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

int isOnButton(Button* button, int posX, int posY) {
    if(posX >= button->posX && posX <= button->posX + button->width && posY>=button->posY && posY<=button->posY+button->height)
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
    ihm->sliderLuminosite    = makeSlider(200,160,100,luminosite,"luminosite");
    ihm->sliderContraste     = makeSlider(200,260,100,contraste,"contraste");
    ihm->sliderSaturation    = makeSlider(200,360,100,saturation,"saturation");
    ihm->sliderOpacite       = makeSlider(100,360,100,opacite,"opacite");
    ihm->btnCalque           = makeButton(190,40,50,560,"Nouveau calque",calque);
    ihm->btnImage            = makeButton(190,40,50,620,"Charger image",charger);
    ihm->btnCalquesSelection = makeButtonCalque(1);
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
    button->posY       = posY;
    button->title      = title;
    button->isSelected = 0;
    return button;
}

void dessinIHM(IHM* ihm, Image* img, SDL_Surface* framebuffer) {
    reshape(ihm->windowWidth,ihm->filterHeight,0,0);
        glPushMatrix();
        glScalef(ihm->windowWidth, ihm->filterHeight,1);
        dessinCarre(1, ColorRGB(1,1,1));
        glPopMatrix();


        ButtonCalque * btc = ihm->btnCalquesSelection;
        Calque* current = img->listCalques;
        while(btc!=NULL) {
            // printf("id du button courrant : %d\n",btc->id);
         glPushMatrix();
         glTranslatef(btc->btn->posX,btc->btn->posY,0);
         glScalef(50,50,1);
         if(btc->btn->isSelected == 0)
            dessinCarre(0,ColorRGB(0.5,0.5,0.5));
         else
            dessinCarre(1,ColorRGB(0.5,0.5,0.5));

            glPushMatrix();
            glTranslatef(0.4, 0.5, 0);
            glColor3d(1, 0, 0);
            char str[10];

            sprintf(str, "%d", btc->id);
            if(btc->id == 1)
                vBitmapOutput(0, 0, "F", GLUT_BITMAP_HELVETICA_18);
            else
                vBitmapOutput(0, 0, str, GLUT_BITMAP_HELVETICA_18);
            glPopMatrix();
         glPopMatrix();
         if(btc->next!=NULL)
             btc=btc->next;
         else
             break;
        }

    reshape(ihm->windowWidth,ihm->windowHeight,0,ihm->filterHeight);
    drawImage(img, framebuffer);

    reshape(ihm->paramWidth,ihm->windowHeight+ihm->filterHeight, ihm->windowWidth, 0);
        glPushMatrix();
            glScalef(ihm->paramWidth, ihm->windowHeight + ihm->filterHeight,1);
            dessinCarre(1, ColorRGB(52./255.,73./255.,94./255.));
        glPopMatrix();
        drawImageHistogramme(img);
        drawSlider(ihm->sliderLuminosite);
        drawSlider(ihm->sliderContraste);
        // drawSlider(ihm->sliderSaturation);
        drawSlider(ihm->sliderOpacite);
        DessinButton(ihm->btnCalque);
        DessinButton(ihm->btnImage);
}

ButtonCalque* makeButtonCalque(int id) {
    ButtonCalque* buttonCalque = malloc(sizeof(ButtonCalque));
    if(!buttonCalque){
        fprintf(stderr, "Probleme Allocation ButtonCalque\n");
        return NULL;
    }
    buttonCalque->btn = makeButton(50, 50, id*60, 10, "1", select);
    buttonCalque->id = id;
    buttonCalque->next = NULL;
    return buttonCalque;
}

void addButtonCalque(IHM* ihm, int id) {
    ButtonCalque* tmp = ihm->btnCalquesSelection;
    ButtonCalque* newButtonCalque = makeButtonCalque(id);
    if(!newButtonCalque)
        return;
    ButtonCalque* last = newButtonCalque;

    while (ihm->btnCalquesSelection->next != NULL) {
        ihm->btnCalquesSelection = ihm->btnCalquesSelection->next;
    }

    ihm->btnCalquesSelection->next = newButtonCalque;
    ihm->btnCalquesSelection = tmp;
}
