#include "glut_tools.h"
#include <string.h>

void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
}

void vBitmapOutput(int x, int y, char *string, void *font) {
	int len, i; // len donne la longueur de la cha�ne de caract�res
	glRasterPos2f(x, y); // Positionne le premier caract�re de la cha�ne
	len = (int) strlen(string); // Calcule la longueur de la cha�ne
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]); // Affiche chaque caract�re de la cha�ne
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font) {
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilis�es pour sauvegarder
	// et restaurer les syst�mes de coordonn�es non translat�s
	glTranslatef(x, y, 0); // Positionne le premier caract�re de la cha�ne
	for (p = string; *p; p++)
		glutStrokeCharacter(font, *p); // Affiche chaque caract�re de la cha�ne
	glPopMatrix();
}
