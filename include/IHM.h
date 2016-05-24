#ifndef _IHM_H_
#define _IHM_H_

#include "Calque.h"
#include <SDL/SDL.h>
#include "sdl_tools.h"
#include "LUT.h"

typedef enum _sliderName {contraste, luminosite, saturation,opacite} SliderName;
typedef enum _btnName {calque, charger} BtnName;

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
        isSelected;
    char* title;
    BtnName name;
} Button;

typedef struct IHM{
    int windowWidth,
        windowHeight,
        paramWidth,
        filterHeight;
    Slider* sliderContraste;
    Slider* sliderLuminosite;
    Slider* sliderSaturation;
    Slider* sliderOpacite;
    Button* btnCalque;
    Button* btnImage;
} IHM;

void dessinIHM(IHM* ihm);
int isOnLuminosite(int posX, int posY, int xLuminosite);
int isOnContraste(int posX, int posY, int xContraste);
int isOnSaturation(int posX, int posY, int xSaturation);
int isOnOpacite(int posX, int posY, int xOpacite);
int isOnChargerImage(int posX, int posY);
int isOnNouveauCalque(int posX, int posY);

Slider* makeSlider(int width, int posY, int posSlider, SliderName name, char* title);
Button* makeButton(int width, int height, int posX, int posY, char* title, BtnName name);
IHM* makeIHM(int windowWidth, int windowHeight, int paramWidth, int filterHeight);
void drawSlider(Slider* slider);

#endif
