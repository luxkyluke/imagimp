#ifndef _PPM_H
#define _PPM_H

#include "bool.h"

unsigned char *PPM_lire(const char *nom_fichier, int *largeur, int *hauteur);
bool PPM_ecrire(const char *nom_fichier, unsigned char *rvb, unsigned l, unsigned h);

#endif
