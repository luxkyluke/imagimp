#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "glut_tools.h"
#include "Image.h"
#include "Histogramme.h"
#include "LUT.h"
#include "Color3f.h"
#include "../include/Geometry.h"
#include "LutOption.h"
#include "Effet.h"
#include "bool.h"

#include "IHM.h"

#define SAVE_PATH "images/save.ppm"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static unsigned int WINDOW_WIDTH_PARAM = 300;
static unsigned int WINDOW_HEIGHT_FILTER = 200;

void nextFrame(SDL_Surface *framebuffer, SDL_Surface *screen) {
	/* On copie le framebuffer ï¿½ l'ï¿½cran */
	SDL_BlitSurface(framebuffer, NULL, screen, NULL);

	SDL_Flip(screen);

	SDL_GL_SwapBuffers();
}

int main(int argc, char** argv) {
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	int nb_source = 6;
	const char *tab_source_img[nb_source];
	tab_source_img[0] = "images/space.ppm";
	tab_source_img[1] = "images/tarte.ppm";
	tab_source_img[2] = "images/coquine.ppm";
	tab_source_img[3] = "images/cute.ppm";
	tab_source_img[4] = "images/pink_floyd.ppm";
	tab_source_img[5] = "images/lake.ppm";
	int id_source = 0;

	IHM*ihm = makeIHM(800, 600, 300, 200);

	SDL_Surface* screen = NULL;
	if (NULL
			== (screen = SDL_SetVideoMode(WINDOW_WIDTH + WINDOW_WIDTH_PARAM,
					WINDOW_HEIGHT + WINDOW_HEIGHT_FILTER, 32,
					SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_OPENGL
							| SDL_GL_DOUBLEBUFFER))) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	// reshape(WINDOW_WIDTH,WINDOW_HEIGHT,0);
	// reshape(WINDOW_WIDTH_PARAM,WINDOW_HEIGHT, WINDOW_WIDTH);
	/* Ouverture d'une fenÃªtre et crÃ©ation d'un contexte OpenGL */
	SDL_WM_SetCaption("Imagimp", NULL);

	printf("L'initialisation.\n");

	/* Crï¿½ation d'une surface SDL dans laquelle le raytracer dessinera */
	SDL_Surface* framebuffer = NULL;
	if (!(framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH,
			WINDOW_HEIGHT, 24, 0, 0, 0, 0))) {
		fprintf(stderr,
				"Erreur d'allocation pour le framebuffer. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	/* Initialisation de la SDL */
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return false;
	}

	initGlut(argc, argv);

	Image* img = makeImage(1600, 1200);
	int idC1;	// idC2, idC3, idC4, idC5, idC6;
	// Image *img;
	// makeImage(img, 512, 512);

	idC1 = chargerImage(img, "images/space.ppm", 1600, 1200, 0.2);
	chargerImage(img, "images/tarte.ppm", 1600, 1200, 0.2);
	chargerImage(img, "images/pink_floyd.ppm", 1600, 1200, 0.2);
//	idC4 = chargerImage(img, "images/coquine.ppm", 1600, 1200, 0.2);
//	idC5 = chargerImage(img, "images/cute.ppm", 1600, 1200, 0.2);
//	idC6 = chargerImage(img, "images/lake.ppm", 1600, 1200, 0.3);

//	changeFusionClaqueToAdditive(img, idC2);

//	LUT* l = makeLUT();
//	INVERT(l);
//	//ADDLUM(l, 50);
//	addLUT(l, l->lut);

	addLUTCalqueById(img, idC1, dimcon, 40);

	//addEffetCalqueById(img, idCalqueImg2, sepia);
//	noirEtBlanc(img->calque_resultat);

	//idLut2 = addLUTCalqueById(img, idCalqueImg, invert, 0);
//	idLut1 = addLUTCalqueById(img, idCalqueImg, addlum, 100);
//	appliqueLUTCalqueByIds(img, idCalqueImg, idLut1);
	//appliqueAllLUTCalqueById(img, idCalqueImg);
//	idLut2 = addLUTCalqueById(img, idCalqueImg2, invert, 0);
//	idLut1 = addLUTCalqueById(img, idCalqueImg1, addlum, 100);

//		for(int i= 0; i<256; i++){
//		printf("lut[%d] = %d\n", i, LUT->lut[i]);
//	}*/

	//freeLUT(LUT)LUT* copyLUT(LUT* l);
	// chargerImage(&img, "images/Baboon.512.ppm", 512, 512);
	fusionnerCalquesImage(img);
	// afficheCalqueById(img, 2);

	int loop = 1;	//, current = 0;
	int posX = 0, posY = 0;

	initBtnIHM(ihm, img->listCalques);
	ButtonCalque * btc = ihm->btnCalquesSelection;

	bool change = true;
	int luminositeCheck = 0, xLuminosite = 0, contrasteCheck = 0,
			xContraste = 0, xOpacite = 0, opaciteCheck = 0; //saturationCheck = 0, xSaturation = 0,

	while (loop) {

		SDL_FillRect(framebuffer, NULL,
				SDL_MapRGB(framebuffer->format, 0, 0, 0));

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* Nettoyage du framebuffer */
		// SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));

		//if modif de l'utilisateur
//		if()
//		updateImage(img);
		if (change) {
			dessinIHM(ihm, img, framebuffer);
			nextFrame(framebuffer, screen);
		}

		// Calque * currentCalque = img->listCalques;
		SDL_Event e;
		change = false;
//		printf("Affichage\n");
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				loop = 0;
				break;
			}

			switch (e.type) {
			case SDL_MOUSEMOTION:
				posX = e.button.x;
				posY = e.button.y;
				if (luminositeCheck == 1 && posX >= WINDOW_WIDTH + 50
						&& posX <= WINDOW_WIDTH + 250) {
					xLuminosite = WINDOW_WIDTH + 150 - posX;
					ihm->sliderLuminosite->posSlider =
							ihm->sliderLuminosite->startPos - xLuminosite;
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				if (contrasteCheck == 1 && posX >= WINDOW_WIDTH + 50
						&& posX <= WINDOW_WIDTH + 250) {
					xContraste = WINDOW_WIDTH + 150 - posX;
					ihm->sliderContraste->posSlider =
							ihm->sliderContraste->startPos - xContraste;
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				if (opaciteCheck == 1 && posX >= ihm->windowWidth + 50
						&& posX <= ihm->windowWidth + 150) {
					xOpacite = ihm->windowWidth + (ihm->paramWidth / 2) - posX;
					ihm->sliderOpacite->posSlider =
							((ihm->sliderOpacite->startPos) - xOpacite);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				break;

			case SDL_MOUSEBUTTONDOWN:
				change = true;
				printf("posX : %d posY : %d\n", posX, posY);

				// Changer le check des sliders.
				if (isOnLuminosite(posX, posY, xLuminosite) == 1)
					luminositeCheck = 1;

				if (isOnContraste(posX, posY, xContraste) == 1)
					contrasteCheck = 1;

				if (isOnOpacite(posX, posY, xOpacite) == 1)
					opaciteCheck = 1;

				// Ajouter un nouveau calque.
				if (isOnButton(ihm->btnCalque, posX - ihm->windowWidth, posY)
						== 1) {
					printf("Il est sur le calque.\n");
					addNewCalque(img->listCalques, 1);
				}

				// Charger une image.
				if (isOnButton(ihm->btnImage, posX - ihm->windowWidth, posY)== 1) {

					if (id_source >= nb_source)
						break;
					const char* name_fichier = tab_source_img[id_source++];
					int id = chargerImage(img, name_fichier, 1600, 1200, 1.);

					addButtonCalque(ihm, id);
				}

				// Supprimer un calque.
				if (isOnButton(ihm->btnDelete, posX, posY-ihm->windowHeight)== 1) {
					suppButton(ihm, img);
				}

				// Évènements pour tous les boutons de calque.
				while (btc != NULL) {
					if (isOnButton(btc->btn, posX, posY - ihm->windowHeight)
							== 1)
						eventButtonCalque(img, ihm, btc->id);

					if (btc->next != NULL)
						btc = btc->next;
					else
						break;
				}
				btc = ihm->btnCalquesSelection;

				// Reset contraste.
				if(isOnButton(ihm->rstContraste, posX-ihm->windowWidth, posY)) {
					xContraste = 0;
					resetContraste(img, ihm, framebuffer, screen);
				}

				// Reset luminosité.
				if(isOnButton(ihm->rstLuminosite, posX-ihm->windowWidth, posY)) {
					xLuminosite = 0;
					resetLuminosite(img, ihm, framebuffer, screen);
				}

				// Reset opacité.
				if(isOnButton(ihm->rstAlpha, posX-ihm->windowWidth, posY)) {
					xOpacite = 0;
					resetOpacite(img, ihm, framebuffer, screen);
				}

				// Mettre en Négatif.
				if(isOnButton(ihm->btnInvert,posX-ihm->windowWidth,posY)) {
					switchInvert(img,ihm);
					eventButtonCalque(img,ihm,ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				// Ajouter l'effet Noir et blanc.
				if(isOnButton(ihm->btnEffetNB,posX,posY-ihm->windowHeight)) {
					addEffetCalqueById(img, ihm->currentCalque, noir_et_blanc);
					eventButtonCalque(img,ihm,ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				// Ajouter l'effet Sepia.
				if(isOnButton(ihm->btnEffetSepia,posX,posY-ihm->windowHeight)) {
					addEffetCalqueById(img, ihm->currentCalque, sepia);
					eventButtonCalque(img,ihm,ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}


				break;

			case SDL_MOUSEBUTTONUP:
				//modification luminosit�
				if (luminositeCheck == 1) {
					Calque* c = getCalqueById(img->listCalques,
							ihm->currentCalque);
					if (existLUTCalqueType(c, addlum)) {
						removeLUTByType(&(c->listLuts), addlum);
						LUT* tmp = c->listLuts;
						while (tmp != NULL) {
							printf("lut lum %d\n", tmp->type);
							tmp = tmp->next;
							if (tmp == c->listLuts) {
								printf("egale");
								break;
							}
						}
					}
					addLUTCalqueById(img, ihm->currentCalque, addlum,
							ihm->sliderLuminosite->posSlider - 100);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}
				//modificatoin du contraste
				if (contrasteCheck == 1) {
					Calque* c = getCalqueById(img->listCalques,
							ihm->currentCalque);
					if (existLUTCalqueType(c, addcon)){
						removeLUTByType(&(c->listLuts), addcon);
						LUT* tmp = c->listLuts;
						while (tmp != NULL) {
							printf("lut addcontraste %d\n", tmp->type);
							tmp = tmp->next;
							if (tmp == c->listLuts) {
								printf("egale");
								break;
							}
						}

					}
					if (existLUTCalqueType(c, dimcon)){
						removeLUTByType(&(c->listLuts), dimcon);
						LUT* tmp = c->listLuts;
						while (tmp != NULL) {
							printf("lut dimcon %d\n", tmp->type);
							tmp = tmp->next;
							if (tmp == c->listLuts) {
								printf("egale");
								break;
							}
						}

					}
					int contraste = ihm->sliderContraste->posSlider - 100;
					if (contraste < 0) {
						addLUTCalqueById(img, ihm->currentCalque, dimcon,
								100 - -1 * contraste);
					} else {
						addLUTCalqueById(img, ihm->currentCalque, addcon,
								contraste);
					}

					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				if (opaciteCheck == 1) {
					Calque* c = getCalqueById(img->listCalques,
							ihm->currentCalque);
					c->alpha = (float) ihm->sliderOpacite->posSlider / 100;
					printf("alpha : %f\n", c->alpha);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				luminositeCheck = 0;
				contrasteCheck = 0;
//				saturationCheck = 0;
				opaciteCheck = 0;
				break;
			}
		}
	}

	//saveImage(img, SAVE_PATH);
	freeImage(img);

	SDL_Quit();

	return EXIT_SUCCESS;
}

// case SDL_KEYDOWN:
// if(e.key.keysym.sym == ':') {
//  keyboard[iterateurKeyboard] = 47;
// } else if(e.key.keysym.sym == 13) {
//  keyboard[iterateurKeyboard]=46;
//  keyboard[iterateurKeyboard+1]=112;
//  keyboard[iterateurKeyboard+2]=112;
//  keyboard[iterateurKeyboard+3]=109;
//  char *tmp = strdup(keyboard);
//  strcpy(keyboard, "images/");
//  strcat(keyboard, tmp);
//  printf("%s\n",keyboard);
//  strcpy(keyboard,"");
//  iterateurKeyboard = 0;
//  free(tmp);
//  // char * nomImage = strcat("images/",keyboard);
//  // nomImage = strcat(nomImage,".ppm");
// } else{
//  keyboard[iterateurKeyboard] = e.key.keysym.sym;
// }
// iterateurKeyboard++;
//     break;
// }
