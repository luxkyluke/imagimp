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

int main(int argc, char** argv) {
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	int nb_source = 4;
	const char *tab_source_img[nb_source];
	tab_source_img[0] = "images/space.ppm";
	tab_source_img[1] = "images/tarte.ppm";
	tab_source_img[2] = "images/cute.ppm";
	tab_source_img[3] = "images/lake.ppm";
	int id_source = 3;

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

	Image* img = makeImage(800, 600);
	int idC1, idC2;

	idC2 = chargerImage(img, "images/lake.ppm", 800, 600, 0.5);
	idC1 = chargerImage(img, "images/space.ppm", 800, 600, 0.5);
	chargerImage(img, "images/tarte.ppm", 800, 600, 0.2);
	fusionnerCalquesImage(img);

	int loop = 1;
	int posX = 0, posY = 0;

	initBtnIHM(ihm, img->listCalques);
	ButtonCalque * btc = ihm->btnCalquesSelection;

	bool change = true;

	int luminositeCheck = 0, xLuminosite = 0, contrasteCheck = 0,
			xContraste = 0, xOpacite = 0, opaciteCheck = 0;

	while (loop) {

		SDL_FillRect(framebuffer, NULL,
				SDL_MapRGB(framebuffer->format, 0, 0, 0));

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (change) {
			dessinIHM(ihm, img, framebuffer);
			nextFrame(framebuffer, screen);
		}

		SDL_Event e;
		change = false;
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

				else if (contrasteCheck == 1 && posX >= WINDOW_WIDTH + 50
						&& posX <= WINDOW_WIDTH + 250) {
					xContraste = WINDOW_WIDTH + 150 - posX;
					ihm->sliderContraste->posSlider =
							ihm->sliderContraste->startPos - xContraste;
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);

				}

				else if (opaciteCheck == 1 && posX >= ihm->windowWidth + 50
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

				else if (isOnContraste(posX, posY, xContraste) == 1)
					contrasteCheck = 1;

				else if (isOnOpacite(posX, posY, xOpacite) == 1)
					opaciteCheck = 1;

				// Ajouter un nouveau calque.
				else if (isOnButton(ihm->btnCalque, posX - ihm->windowWidth,posY) == 1) {
					int i = id_source++;
					i = i%nb_source;
					const char* name_fichier = tab_source_img[i];
					int id = chargerImage(img, name_fichier, 800, 600, 1.);
					if(id!=0) {
						afficheCalqueById(img, id);
						addButtonCalque(ihm, id);
						ihm->currentCalque = id;
					}
				}

				// Charger une image.
				else if (isOnButton(ihm->btnImage, posX - ihm->windowWidth,
						posY) == 1) {

					if (id_source >= nb_source)
						break;
					char insert_fichier[100];
					printf("\nTaper le nom de l'image precede de images/ : ");
					scanf("%s", insert_fichier);
					int id = chargerImage(img, insert_fichier, 800, 600, 1.);
					if(id!=0) {
						afficheCalqueById(img, id);
						addButtonCalque(ihm, id);
						ihm->currentCalque = id;
					}
				}

				// Sauvegarder une image.
				else if (isOnButton(ihm->btnSave, posX - ihm->windowWidth, posY)== 1) {
					saveImage(img, SAVE_PATH);
				}

				// Supprimer un calque.
				else if (isOnButton(ihm->btnDelete, posX,posY - ihm->windowHeight) == 1) {
					suppButton(ihm, img);
				}

				// Évènements pour tous les boutons de calque.
				else {
					while (btc != NULL) {
						if (isOnButton(btc->btn, posX, posY - ihm->windowHeight)== 1) {
							eventButtonCalque(img, ihm, btc->id);
						}

						if (btc->next != NULL)
							btc = btc->next;
						else
							break;
					}
					btc = ihm->btnCalquesSelection;
				}

				// Reset contraste.
				if (isOnButton(ihm->rstContraste, posX - ihm->windowWidth,
						posY)) {
					xContraste = 0;
					resetContraste(img, ihm,true);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);

				}

				// Reset luminosité.
				else if (isOnButton(ihm->rstLuminosite, posX - ihm->windowWidth,
						posY)) {
					xLuminosite = 0;
					resetLUT(img, ihm, addlum, ihm->sliderLuminosite,true);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);

				}

				// Reset opacité.
				else if (isOnButton(ihm->rstAlpha, posX - ihm->windowWidth,
						posY)) {
					xOpacite = 0;
					resetOpacite(img, ihm, ihm->sliderOpacite,true);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);

				}

				// Mettre en Négatif.
				else if (isOnButton(ihm->btnInvert, posX - ihm->windowWidth,
						posY)) {
					switchInvert(img, ihm);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				// Ajouter l'effet Noir et blanc.
				else if (isOnButton(ihm->btnEffetNB, posX,
						posY - ihm->windowHeight)) {
					switchEffectById(img, ihm->currentCalque, noir_et_blanc);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				else if (isOnButton(ihm->btnFusion, posX - ihm->windowWidth,
						posY)) {
					Calque* c = getCalqueById(img->listCalques,
							ihm->currentCalque);
					switchFusion(c);
				}

				// Ajouter l'effet Sepia.
				else if (isOnButton(ihm->btnEffetSepia, posX,
						posY - ihm->windowHeight)) {
					switchEffectById(img, ihm->currentCalque, sepia);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}
				break;

			case SDL_MOUSEBUTTONUP:
				//modification luminosité
				if (luminositeCheck == 1) {
					resetLUT(img, ihm, addlum, ihm->sliderLuminosite,false);
					addLUTCalqueById(img, ihm->currentCalque, addlum,ihm->sliderLuminosite->posSlider - 100);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}
				//modificatoin du contraste
				else if (contrasteCheck == 1) {
					changeContraste(img, ihm);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);

				} else if (opaciteCheck == 1) {
					modifyOppacityCalqueById(img, ihm->currentCalque, ihm->sliderOpacite->posSlider/100.);
					eventButtonCalque(img, ihm, ihm->currentCalque);
					dessinIHM(ihm, img, framebuffer);
					nextFrame(framebuffer, screen);
				}

				luminositeCheck = 0;
				contrasteCheck = 0;
				opaciteCheck = 0;
				break;
			}
		}
	}
	freeImage(img);

	SDL_Quit();

	return EXIT_SUCCESS;
}
