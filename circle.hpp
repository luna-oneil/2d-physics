#pragma once

#include <SDL3/SDL_pixels.h>
#include <cstdint>
#include "vector2d.hpp"

class Circle {
private:
    Vector2d pos;
    Vector2d vel;
    double radius;
    SDL_Color color;


public:
    Circle(double x, double y, double radius, uint8_t r, uint8_t g, uint8_t b);
    Circle();
    const Vector2d get_pos() const;
    const Vector2d get_vel() const;
    const SDL_Color get_color() const;
    double get_radius() const;
    void accelerate(Vector2d &vector);
    void accelerate(double x, double y);
    void move();
    void mirror_vel(bool y_axis);
};
