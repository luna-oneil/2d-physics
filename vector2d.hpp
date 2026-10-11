#pragma once

class Vector2d {
public:
    double x;
    double y;
    Vector2d(): x(0), y(0) {}
    Vector2d(double x, double y): x(x), y(y) {}
    void move(double x, double y);
    void set(double x, double y);
    void move(Vector2d &vector);
    void set(Vector2d &vector);
    // operator overloads
    Vector2d operator+(const Vector2d &right) const;
    Vector2d operator-(const Vector2d &right) const;
    // rotates x and y 90 degrees around the origin
    Vector2d Vector2d::rotated90() const;
};
