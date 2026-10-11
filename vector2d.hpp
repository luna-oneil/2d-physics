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
    // rotates x and y 90 degrees around the origin
    Vector2d rotated90() const;
    // operator overloads
    Vector2d operator+(const Vector2d &right) const;
    Vector2d operator-(const Vector2d &right) const;
    Vector2d operator*(double scalar) const;
    Vector2d operator/(double scalar) const;
    Vector2d& operator+=(const Vector2d &right);
    Vector2d& operator-=(const Vector2d &right);
    Vector2d& operator*=(double scalar);
    Vector2d& operator/=(double scalar);
    // friend functions
    friend double dot_product(const Vector2d &v1, const Vector2d &v2);
};
