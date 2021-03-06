#ifndef _IHM_H_
#define _IHM_H_

#include "Calque.h"
#include <SDL/SDL.h>
#include "sdl_tools.h"
#include "LUT.h"
#include "Image.h"
#include "bool.h"

typedef enum _sliderName {contraste, luminosite, saturation,opacite} SliderName;
typedef enum _btnName {calque, charger, select, supprimer, rstContraste, rstLuminosite, rstAlpha, switchfusion,invertbtn,sepiabtn,nb,save,btnfusion} BtnName;


typedef struct Slider{
    int width;
    int posSlider;
    int posY;
    int startPos;
    SliderName name;
    char* title;
} Slider;

typedef struct Button{
    int width,
        height,
        posX,
        posY,
        isSelected;
    char* title;
    BtnName name;
} Button;

typedef struct ButtonCalque {
    Button* btn;
    struct ButtonCalque* next;
    int id;
    int pos;
} ButtonCalque;

typedef struct IHM{
    int windowWidth,
        windowHeight,
        paramWidth,
        filterHeight,
        currentCalque,
        nbButtons;
    Slider*  sliderContraste;
    Slider*  sliderLuminosite;
    Slider*  sliderSaturation;
    Slider*  sliderOpacite;
    Button*  btnCalque;
    Button*  btnImage;
    Button*  btnSave;

    ButtonCalque*  btnCalquesSelection;

    Button*  rstContraste;
    Button*  rstLuminosite;
    Button*  rstAlpha;
    Button*  btnDelete;
    Button*  btnEffetNB;
    Button*  btnEffetSepia;
    Button*  btnInvert;
    Button*  btnFusion;

} IHM;

void dessinIHM(IHM* ihm, Image* img, SDL_Surface* framebuffer);
int isOnLuminosite(int posX, int posY, int xLuminosite);
int isOnContraste(int posX, int posY, int xContraste);
int isOnSaturation(int posX, int posY, int xSaturation);
int isOnOpacite(int posX, int posY, int xOpacite);
int isOnButton(Button* button, int posX, int posY);
void initBtnIHM(IHM *ihm, Calque* c);
void suppButton(IHM* ihm, Image *img);
void changeContraste(Image *img,IHM *ihm);
ButtonCalque* makeButtonCalque(int id, int pos);
void addButtonCalque(IHM* ihm,int id);
void removeButtonCalque(IHM* ihm, int id);
void reshape(unsigned int windowWidth, unsigned int windowHeight, int xViewport,int yViewport);
void setVideoMode(unsigned int windowWidth, unsigned int windowHeight);
Slider* makeSlider(int width, int posY, int posSlider, SliderName name, char* title);
Button* makeButton(int width, int height, int posX, int posY, char* title, BtnName name);
IHM* makeIHM(int windowWidth, int windowHeight, int paramWidth, int filterHeight);
void drawSlider(Slider* slider);
void freeButtonCalque(IHM* ihm, int id);
void eventButtonCalque(Image* img, IHM* ihm, int id);
bool resetLUT(Image* img, IHM* ihm, LutOption lut, Slider* slider, bool resetSlider);
bool resetContraste(Image* img, IHM* ihm, bool resetSlider);
void resetOpacite(Image* img, IHM* ihm, Slider* slider, bool resetSlider);
void switchInvert(Image* img, IHM* ihm);
void switchFusion(Calque*c);
void nextFrame(SDL_Surface *framebuffer, SDL_Surface *screen);
#endif
