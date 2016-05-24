#ifndef COLOR3F_H_
#define COLOR3F_H_

typedef struct {
    float r, g, b;
} Color3f;

Color3f ColorRGB(float r, float g, float b);
Color3f ColorGrey(float grey);
Color3f AddColors(Color3f lhs, Color3f rhs);
Color3f SubColors(Color3f lhs, Color3f rhs);
Color3f MultColors(Color3f lhs, Color3f rhs);
Color3f DivColors(Color3f lhs, Color3f rhs);
Color3f MultColor(Color3f c, float a);
Color3f DivColor(Color3f c, float a);

extern Color3f BLACK, WHITE, RED, GREEN, BLUE;

#endif
