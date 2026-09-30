#include "vector2d.hpp"

void Vector2d::move(double x, double y) {
    this->x += x;
    this->y += y;
}

void Vector2d::move(Vector2d &vector) {
    this->x += vector.x;
    this->y += vector.y;
}

void Vector2d::set(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vector2d::set(Vector2d &vector) {
    this->x = vector.x;
    this->y = vector.y;
}
