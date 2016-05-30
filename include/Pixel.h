#ifndef _PIXEL_H_
#define _PIXEL_H_

typedef struct pixel{
	unsigned int r;
	unsigned int g;
	unsigned int b;
}Pixel;

Pixel makePixel(unsigned int r, unsigned int g, unsigned int b);
void checkValue(int *value);

#endif
