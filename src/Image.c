#include "Image.h"
#include "Histogramme.h"

Image*  makeImage(int width, int height, float op){
	Image* img = (Image*) malloc(sizeof(Image));
	img->listCalques = makeCalque(width, height, op);
	return img;
}

void chargerImage(Image* img, char * pathImg, int width, int height, float op){
	chargerImageCalque(img->listCalques, pathImg, width, height, op);
}

void appliqueLUTCalqueId(Image* img, int id, LUT* lut){
	if(LUTIsEmpty(lut) || !img)
		return;
	Calque* c = getCalqueById(img->listCalques, id);
	appliquerLUT(lut, c);
}

void printImage(Image* img, SDL_Surface* framebuffer){
	if(!img || !img->listCalques){
		printf("Impossible d'afficher ! Image vide ou NULL\n");
		return ;
	}
	int i, j;
	Calque* c = img->listCalques;
	fusionnerCalque(c);
	glPushMatrix();
	for (i = 0; i < c->height; i++) {
		for (j = 0; j < c->width; j++) {
			int r = c->pixels[j][i].r;
			int g = c->pixels[j][i].g;
			int b = c->pixels[j][i].b;
			//Uint32  color = SDL_MapRGB(framebuffer->format, r, g, b);
			//Uint32  color = SDL_MapRGB(framebuffer->format, 0, 0, 0);
			// PutPixel(framebuffer, j, i, color);

			glBegin(GL_POINTS);
				glColor3f(r/255., g/255., b/255.);
				glVertex2i(j,i);
			glEnd();

		}
	}
	glPopMatrix();
}
