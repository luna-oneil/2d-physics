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
};
