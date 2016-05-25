#include <stdlib.h>
#include <stdio.h>
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

#include "IHM.h"

#define SAVE_PATH "images/save.ppm"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static unsigned int WINDOW_WIDTH_PARAM = 300;
static unsigned int WINDOW_HEIGHT_FILTER = 200;
static const unsigned int BIT_PER_PIXEL = 24;


//redimenssionne la fenetre SDL
void reshape(unsigned int windowWidth, unsigned int windowHeight, int xViewport, int yViewport) {
	glViewport(xViewport, yViewport, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0., windowWidth, windowHeight, 0.);
}

//Ouvre la fenetre SDL
void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
	if (NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL,
	SDL_OPENGL | SDL_GL_DOUBLEBUFFER | 1)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv) {
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	IHM*ihm = makeIHM(800,600,300,200);


	SDL_Surface* screen = NULL;
	if (NULL
			== (screen = SDL_SetVideoMode(WINDOW_WIDTH+WINDOW_WIDTH_PARAM, WINDOW_HEIGHT + WINDOW_HEIGHT_FILTER,
					BIT_PER_PIXEL, SDL_DOUBLEBUF | SDL_RESIZABLE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER))) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	// reshape(WINDOW_WIDTH,WINDOW_HEIGHT,0);
	// reshape(WINDOW_WIDTH_PARAM,WINDOW_HEIGHT, WINDOW_WIDTH);
	/* Ouverture d'une fenêtre et création d'un contexte OpenGL */
	SDL_WM_SetCaption("Imagimp", NULL);

	printf("L'initialisation.\n");

	/* Cr�ation d'une surface SDL dans laquelle le raytracer dessinera */
	SDL_Surface* framebuffer = NULL;
	if (NULL
			== (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH,
					WINDOW_HEIGHT, 24, 0, 0, 0, 0))) {
		fprintf(stderr,
				"Erreur d'allocation pour le framebuffer. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	/* Initialisation de la SDL */
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,"Impossible d'initialiser la SDL. Fin du programme.\n");
		return false;
	}

	initGlut(argc,argv);

	Image* img = makeImage(512, 512);
	int idCalqueImg1, idCalqueImg2, idLut2, idLut1;
	// Image *img;
	// makeImage(img, 512, 512);
	idCalqueImg1 = chargerImage(img, "images/Aerial.512.ppm", 512, 512, 1.);
	idCalqueImg2 = chargerImage(img, "images/Baboon.ppm", 512, 512, 1.);
	addButtonCalque(ihm,2);
	addButtonCalque(ihm,3);

	ButtonCalque * btc = ihm->btnCalquesSelection;

//	LUT* l = makeLUT();
//	INVERT(l);
//	//ADDLUM(l, 50);
//	addLUT(l, l->lut);

	addEffetCalqueById(img, idCalqueImg2, sepia);
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

	int loop = 1;
	int posX = 0, posY = 0;

	//int change = 0;
	int luminositeCheck = 0, xLuminosite = 0, contrasteCheck = 0, xContraste = 0, saturationCheck = 0, xSaturation = 0;

	while (loop) {
		SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* Nettoyage du framebuffer */
		// SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));

		dessinIHM(ihm,img,framebuffer);


		//if modif de l'utilisateur
//		if()
//		updateImage(img);


		/* On copie le framebuffer � l'�cran */
		SDL_BlitSurface(framebuffer, NULL, screen, NULL);

		SDL_Flip(screen);

		SDL_GL_SwapBuffers();
		// Calque * currentCalque = img->listCalques;
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				loop = 0;
				break;
			}


			switch(e.type) {
				case SDL_MOUSEMOTION:
					posX = e.button.x;
					posY = e.button.y;
					if(luminositeCheck == 1 && posX >= WINDOW_WIDTH+50 && posX <= WINDOW_WIDTH+250) {
						xLuminosite = WINDOW_WIDTH + 150 - posX;
					}

					if(contrasteCheck == 1 && posX >= WINDOW_WIDTH+50 && posX <= WINDOW_WIDTH+250) {
						xContraste = WINDOW_WIDTH + 150 - posX;
					}

					if(saturationCheck == 1 && posX >= WINDOW_WIDTH+50 && posX <= WINDOW_WIDTH+250) {
						xSaturation = WINDOW_WIDTH + 150 - posX;
					}

					break;

				case SDL_MOUSEBUTTONDOWN:
					printf("posX : %d posY : %d\n", posX,posY);
					if(isOnLuminosite(posX,posY,xLuminosite) == 1)
						luminositeCheck = 1;

					if(isOnContraste(posX,posY,xContraste) == 1)
						contrasteCheck = 1;

					if(isOnSaturation(posX,posY,xSaturation) == 1)
						saturationCheck = 1;

					if(isOnButton(ihm->btnCalque,posX - ihm->windowWidth, posY) == 1)
						printf("Il est sur le calque.\n");

					if(isOnButton(ihm->btnImage,posX - ihm->windowWidth, posY) == 1)
						printf("Il est sur le chargement.\n");

					while(btc!=NULL) {
						if(isOnButton(btc->btn, posX, posY - ihm->windowHeight)==1) {
							afficheCalqueById(img,btc->id);
						}
						if(btc->next!=NULL)
						    btc=btc->next;
						else
						    break;
					}
					btc = ihm->btnCalquesSelection;

					break;

				case SDL_MOUSEBUTTONUP:
					luminositeCheck = 0;
					contrasteCheck  = 0;
					saturationCheck = 0;
					break;
			}
		}
	}

	//saveImage(img, SAVE_PATH);
	freeImage(img);

	SDL_Quit();

	return EXIT_SUCCESS;
}
