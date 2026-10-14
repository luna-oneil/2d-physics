#include "circle.hpp"
#include <SDL3/SDL_pixels.h>
#include <cstdint>

Circle::Circle(double x, double y, double radius, uint8_t r, uint8_t g, uint8_t b):
    pos(x, y), radius(radius), color{r, g, b, 255} {}

Circle::Circle() : Circle::Circle(0, 0, 10, 255, 255, 255) {}

const Vector2d Circle::get_pos() const {
    return pos;
}

const Vector2d Circle::get_vel() const {
    return vel;
}

const Vector2d Circle::get_force() const {
    return force;
}

const SDL_Color Circle::get_color() const {
    return color;
}

double Circle::get_radius() const {
    return radius;
}

void Circle::add_force(const Vector2d &new_force) {
    force += new_force;
}

void Circle::set_vel(const Vector2d &vector) {
    vel = vector;
}

void Circle::move() {
    vel.move(force);
    force = Vector2d();
    pos.move(vel);
}

void Circle::mirror_vel(bool y_axis) {
    if (y_axis) {
        vel.y = -vel.y;
        return;
    }
    vel.x = -vel.x;
}
