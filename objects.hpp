#pragma once

#include <SDL3/SDL_pixels.h>

struct Coordinates {
    double x;
    double y;
};
typedef struct Coordinates Coordinates;

class Circle {
private:
    Coordinates coords;
    SDL_Color color;
    int radius;


public:
    Circle(double x, double y, int radius, int r, int g, int b);
    Coordinates get_coords();
    SDL_Color get_color();
    int get_radius();
    void update_coords(double delta_x, double delta_y);
};