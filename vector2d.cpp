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
    x = vector.x;
    y = vector.y;
}

Vector2d Vector2d::rotated90() const {
    return Vector2d(-y, x);
}

Vector2d Vector2d::operator+(const Vector2d &right) const {
    Vector2d result(x + right.x, y + right.y);
    return result;
}

Vector2d Vector2d::operator-(const Vector2d &right) const {
    Vector2d result(x - right.x, y - right.y);
    return result;
}

Vector2d Vector2d::operator*(double scalar) const {
    Vector2d result(x * scalar, y * scalar);
    return result;
}

Vector2d Vector2d::operator/(double scalar) const {
    Vector2d result(x / scalar, y / scalar);
    return result;
}

Vector2d& Vector2d::operator+=(const Vector2d &right) {
    x += right.x;
    y += right.y;
    return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d &right) {
    x -= right.x;
    y -= right.y;
    return *this;
}
Vector2d& Vector2d::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2d& Vector2d::operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}
