#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "Image.h"
#include "Histogramme.h"
#include "LUT.h"

static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 1200;
static const unsigned int BIT_PER_PIXEL = 24;


//redimenssionne la fenetre SDL
void reshape(unsigned int windowWidth, unsigned int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100., 100., -100. * (float) windowHeight / (float) windowWidth,
			100. * (float) windowHeight / (float) windowWidth);
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

	SDL_Surface* screen = NULL;
	if (NULL
			== (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT,
					BIT_PER_PIXEL,
					SDL_DOUBLEBUF | SDL_RESIZABLE))) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	/* Ouverture d'une fenêtre et création d'un contexte OpenGL */
	//reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
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


	Image img;
	makeImage(&img, WINDOW_WIDTH, WINDOW_HEIGHT);


	LUT* l = (LUT*) malloc(sizeof(LUT));
	l = makeLUT();
	//INVERT(l);
	ADDLUM(l, 50);
	addLUT(l, l->lut);


	appliqueLUTCalqueId(&img, 0, l);

//		for(int i= 0; i<256; i++){
//		printf("lut[%d] = %d\n", i, LUT->lut[i]);
//	}*/

	//freeLUT(LUT);

	chargerImage(&img, "images/Sylvan_Lake.ppm", WINDOW_WIDTH, WINDOW_HEIGHT);

	int loop = 1;

	int change = 0;

	//printHistogramme(img.listCalques->histogramme);
	while (loop) {

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		/* Nettoyage du framebuffer */
		//SDL_FillRect(framebuffer, NULL,	SDL_MapRGB(framebuffer->format, 0, 0, 0));

		/* Placer ici le code de dessin */
		//PutPixel(framebuffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SDL_MapRGB(framebuffer->format, 255, 255, 255));

		printImage(&img, framebuffer);
		//drawHistogramme(img.listCalques->histogramme);


		SDL_GL_SwapBuffers();

		/* On copie le framebuffer � l'�cran */
		SDL_BlitSurface(framebuffer, NULL, screen, NULL);

		SDL_Flip(screen);

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				loop = 0;
				break;
			}
		}
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}
