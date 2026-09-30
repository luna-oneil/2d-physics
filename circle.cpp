#include "objects.hpp"
#include <SDL3/SDL_pixels.h>
#include <cstdint>

Circle::Circle(double x, double y, double radius, uint8_t r, uint8_t g, uint8_t b) {
    Vector2d pos(x, y);
    Vector2d vel(0, 0);
    this->radius = radius;
    SDL_Color color = {r, g, b, 255};
}

const Vector2d Circle::get_pos() const {
    return pos;
}

const Vector2d Circle::get_vel() const {
    return vel;
}

const SDL_Color Circle::get_color() const {
    return color;
}

double Circle::get_radius() const {
    return radius;
}

void Circle::accelerate(Vector2d &vector) {
    vel.move(vector);
}

void Circle::accelerate(double x, double y) {
    vel.move(x, y);
}

void Circle::move() {
    pos.move(vel);
}
