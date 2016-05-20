#ifndef _PIXEL_H_
#define _PIXEL_H_

typedef struct pixel{
	unsigned int r;
	unsigned int g;
	unsigned int b;
}Pixel;

Pixel makePixel(unsigned int r, unsigned int g, unsigned int b);
//Pixel multiPixelFloat(Pixel p, float a);
//Pixel addPixel(Pixel p , Pixel p2);
//Pixel multiPixel(Pixel p , Pixel p2);
void checkValue(int* value);

#endif
