#include "sdl_tools.h"

GLuint loadImage(char* image){
    glEnable(GL_TEXTURE_2D);
    SDL_Surface* myTexture = IMG_Load(image);
    if (myTexture == NULL){
        fprintf(stderr, "Impossible d'afficher l'image %s\n", image);
        return EXIT_FAILURE;
    } else {
        printf("L'image %s a été chargée correctement\n", image);
    }

    GLuint textures;
    glGenTextures(1, &textures);

    glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    printf("Format : %d\n", myTexture->format->BytesPerPixel);
    switch(myTexture->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
            exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTexture->w, myTexture->h, 0, format, GL_UNSIGNED_BYTE, myTexture->pixels);

    SDL_FreeSurface(myTexture);
    glBindTexture(GL_TEXTURE_2D, 0);
    printf("texutre %d\n", textures);
    glDisable(GL_TEXTURE_2D);
    return textures;
}

void PutPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;

    Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}


Uint32 ColorToPixel(SDL_PixelFormat* format, Color3f color) {
	Uint32 r = 255 * color.r;
	Uint32 g = 255 * color.g;
	Uint32 b = 255 * color.b;
	return SDL_MapRGB(format, CLAMP(r, 0, 255), CLAMP(g, 0, 255), CLAMP(b, 0, 255));
}

