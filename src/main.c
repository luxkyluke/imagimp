#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "Image.h"
#include "Histogramme.h"

static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 1200;
static const unsigned int BIT_PER_PIXEL = 24;

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
	SDL_WM_SetCaption("Imagimp", NULL);

	printf("L'initialisation.\n");

	/* Création d'une surface SDL dans laquelle le raytracer dessinera */
	SDL_Surface* framebuffer = NULL;
	if (NULL
			== (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH,
					WINDOW_HEIGHT, 24, 0, 0, 0, 0))) {
		fprintf(stderr,
				"Erreur d'allocation pour le framebuffer. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	Image img;
	makeImage(&img, WINDOW_WIDTH, WINDOW_HEIGHT);

	LUT* LUT;
	LUT = makeLUT();
	
	addLUT(LUT, LUT->lut);
	ADDLUM(LUT, 10);
		for(int i= 0; i<256; i++){
		printf("lut[%d] = %d\n", i, LUT->lut[i]);
	}

	freeLUT(LUT);





	printf("Tada.\n");
	chargerImage(&img, "images/Sylvan_Lake.ppm", WINDOW_WIDTH, WINDOW_HEIGHT);
	printf("Tada image.\n");

	int loop = 1;

int change = 0;

	while (loop) {
		/* Nettoyage du framebuffer */
		SDL_FillRect(framebuffer, NULL,
				SDL_MapRGB(framebuffer->format, 0, 0, 0));

		/* Placer ici le code de dessin */
		//PutPixel(framebuffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SDL_MapRGB(framebuffer->format, 255, 255, 255));

		printImage(&img, framebuffer);
		drawHistogramme(img.listCalques->histogramme);



		/* On copie le framebuffer à l'écran */
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
