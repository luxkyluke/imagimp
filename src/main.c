#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "sdl_tools.h"
#include "Image.h"
#include "Histogramme.h"
#include "LUT.h"
#include "Color3f.h"

<<<<<<< HEAD
static unsigned int WINDOW_WIDTH = 512;
static unsigned int WINDOW_HEIGHT = 512;

static unsigned int WINDOW_WIDTH_PARAM = 200;
static unsigned int WINDOW_HEIGHT_FILTER = 200;
=======
static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 1200;
>>>>>>> f75c2157425f769a7b23d3695718d27583abaceb
static const unsigned int BIT_PER_PIXEL = 24;


//redimenssionne la fenetre SDL
void reshape(unsigned int windowWidth, unsigned int windowHeight, int xViewport, int yViewport) {
	glViewport(xViewport, yViewport, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0., windowWidth, windowHeight, 0.);
}

void dessinCarre(int fill, Color3f color){
  if (fill == 1){
    glBegin(GL_QUADS);
      glColor3f(color.r,color.g, color.b);
      glVertex2f(0,1); //point de depart
      glVertex2f(1,1); //point d’arrive
      glVertex2f(1,0);
      glVertex2f(0,0);
    glEnd();
  }
  else{
    glBegin(GL_LINE_LOOP);
      glColor3f(color.r,color.g, color.b);
      glVertex2f(-0.5,0.5); //point de depart
      glVertex2f(0.5,0.5); //point d’arrive
      glVertex2f(0.5,-0.5);
      glVertex2f(-0.5,-0.5);
    glEnd();
  }
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

	Image* img = makeImage(WINDOW_WIDTH, WINDOW_HEIGHT, 0.);

<<<<<<< HEAD
	Image img;
	makeImage(&img, 512, 512);
=======
	chargerImage(img, "images/Sylvan_Lake.ppm", WINDOW_WIDTH, WINDOW_HEIGHT, 1.);
>>>>>>> f75c2157425f769a7b23d3695718d27583abaceb

	LUT* l = makeLUT();
	//INVERT(l);
	//ADDLUM(l, 50);
	//addLUT(l, l->lut);

	appliqueLUTCalqueId(img, 0, l);

//		for(int i= 0; i<256; i++){
//		printf("lut[%d] = %d\n", i, LUT->lut[i]);
//	}*/

	//freeLUT(LUT);
	chargerImage(&img, "images/Baboon.512.ppm", 512, 512);


	int loop = 1;

	int change = 0;

	while (loop) {
		SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		reshape(WINDOW_WIDTH_PARAM,WINDOW_HEIGHT_FILTER,0,0);
		glPushMatrix();
			glTranslatef(100,0,0);
			glScalef(WINDOW_WIDTH, WINDOW_HEIGHT_FILTER,100);
			dessinCarre(1, ColorRGB(1,1,1));
		glPopMatrix();

		reshape(WINDOW_WIDTH,WINDOW_HEIGHT,0,WINDOW_HEIGHT_FILTER);
		/* Nettoyage du framebuffer */
		// SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));
<<<<<<< HEAD

		printImage(&img, framebuffer);

		reshape(WINDOW_WIDTH_PARAM,WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT_FILTER);
		drawHistogramme(img.listCalques->histogramme);
=======
		printImage(img, framebuffer);
		drawHistogramme(img->listCalques->histogramme);
>>>>>>> f75c2157425f769a7b23d3695718d27583abaceb


		/* On copie le framebuffer � l'�cran */
		SDL_BlitSurface(framebuffer, NULL, screen, NULL);

		SDL_Flip(screen);

		SDL_GL_SwapBuffers();
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
