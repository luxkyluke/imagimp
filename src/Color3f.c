#include "Color3f.h"

Color3f ColorRGB(float r, float g, float b) {
    Color3f c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

Color3f ColorGrey(float grey) {
    return ColorRGB(grey, grey, grey);
}

Color3f AddColors(Color3f lhs, Color3f rhs) {
    return ColorRGB(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}

Color3f SubColors(Color3f lhs, Color3f rhs) {
    return ColorRGB(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
}

Color3f MultColors(Color3f lhs, Color3f rhs) {
    return ColorRGB(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
}

Color3f DivColors(Color3f lhs, Color3f rhs) {
    return ColorRGB(lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b);
}

Color3f MultColor(Color3f c, float a) {
    return ColorRGB(c.r * a, c.g * a, c.b * a);
}

Color3f DivColor(Color3f c, float a) {
    return ColorRGB(c.r / a, c.g / a, c.b / a);
}

Color3f BLACK = { 0, 0, 0 }, WHITE = { 1, 1, 1 }, RED = { 1, 0, 0 }, GREEN = {
        0, 1, 0 }, BLUE = { 0, 0, 1 };
