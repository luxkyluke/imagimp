#ifndef SDL_TOOLS_H_
#define SDL_TOOLS_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Color3f.h"
#include "Geometry.h"

void PutPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
Uint32 ColorToPixel(SDL_PixelFormat* format, Color3f color);
GLuint loadImage(char* image);
#endif
