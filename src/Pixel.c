#include "Pixel.h"

Pixel makePixel(unsigned int r, unsigned int g, unsigned int b){
	Pixel p;
	p.r=r;
	p.b=b;
	p.g=g;
	return p;
}


//Pixel multiPixelFloat(Pixel p, float a){
//	return makePixel(p.r*a, p.g*a, p.b*a, p.alpha);
//}
//
//Pixel addPixel(Pixel p , Pixel p2){
//	return makePixel(p.r + p2.r, p.g + p2.g, p.b + p2.b, p.alpha + p2.alpha);
//}
//
//Pixel multiPixel(Pixel p , Pixel p2){
//	return makePixel(p.r * p2.r, p.g * p2.g, p.b * p2.b, p.alpha * p2.alpha);
//}

void checkValue(int* value){
	if(*value > 255){
		*value = 255;
		return;
	}
	if(*value < 0){
		*value = 0;
	}
}
