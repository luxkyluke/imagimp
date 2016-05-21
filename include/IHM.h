#ifndef _IHM_H_
#define _IHM_H_

#include "Calque.h"
#include <SDL/SDL.h>
#include "sdl_tools.h"
#include "LUT.h"

void dessinIHM(Calque* c, int xLuminosite, int xContraste, int xSaturation);
int isOnLuminosite(int posX, int posY, int xLuminosite);
int isOnContraste(int posX, int posY, int xContraste);
int isOnSaturation(int posX, int posY, int xSaturation);
int isOnChargerImage(int posX, int posY);
int isOnNouveauCalque(int posX, int posY);

#endif
