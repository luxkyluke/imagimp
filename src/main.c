#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "Image.h"

static unsigned int WINDOW_WIDTH = 1400;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;

int main(int argc, char** argv) {
	if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	SDL_Surface* screen = NULL;
	if (NULL
			== (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT,
					BIT_PER_PIXEL,
					SDL_DOUBLEBUF))) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_WM_SetCaption("Imagimp", NULL);

	printf("L'initialisation.\n");

	/* Cr�ation d'une surface SDL dans laquelle le raytracer dessinera */
	SDL_Surface* framebuffer = NULL;
	if (NULL
			== (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH,
					WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
		fprintf(stderr,
				"Erreur d'allocation pour le framebuffer. Fin du programme.\n");
		return EXIT_FAILURE;
	}

	Image img;
	printf("Tada.\n");
	chargerImage(&img, "images/Baboon.512.ppm", 512, 512);
	printf("Tada image.\n");

	int loop = 1;
	while (loop) {
		/* Nettoyage du framebuffer */
		SDL_FillRect(framebuffer, NULL,
				SDL_MapRGB(framebuffer->format, 0, 0, 0));

		/* Placer ici le code de dessin */
		//PutPixel(framebuffer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, SDL_MapRGB(framebuffer->format, 255, 255, 255));

		printImage(&img, framebuffer);


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
