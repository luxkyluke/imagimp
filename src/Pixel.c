#include "Pixel.h"

Pixel makePixel(int r, int g, int b, float a){
	Pixel p;
	p->r=r;
	p->b=b;
	p->g=g;
	p->alpha=a;
	return p;
}


Pixel multiPixelFloat(Pixel p, float a){
	return makePixel(p.r*a, p.g*a, p.b*a);
}
Pixel addPixel(Pixel p , Pixel p2){
	return makePixel(p.r + p2.r, p.g + p2.g, p.b + p2.b);
}

Pixel multiPixel(Pixel p , Pixel p2){
	return makePixel(p.r * p2.r, p.g * p2.g, p.b * p2.b);
}
