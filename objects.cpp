#include "objects.hpp"
#include <SDL3/SDL_pixels.h>

Circle::Circle(double x, double y, int radius, int r, int g, int b) {
    coords.x = x;
    coords.y = y;
    this->radius = radius;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
}

Coordinates Circle::get_coords() {
    return coords;
}

SDL_Color Circle::get_color() {
    return color;
}

int Circle::get_radius() {
    return radius;
}

void Circle::update_coords(double delta_x, double delta_y) {
    coords.x += delta_x;
    coords.y += delta_y;
}
