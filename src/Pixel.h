#ifndef PIXEL_H_
#define PIXEL_H_

typedef struct pixel{
	int r;
	int g;
	int b;
	float alpha;
}Pixel;

Pixel makePixel(int r, int g, int b, float a);
Pixel multiPixelFloat(Pixel p, float a);
Pixel addPixel(Pixel p , Pixel p2);
Pixel multiPixel(Pixel p , Pixel p2);

#endif
