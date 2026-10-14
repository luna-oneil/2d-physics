#pragma once

#include "vector2d.hpp"
#include "circle.hpp"

class Spring {
private:
    // ci = circle index
    int ci1;
    int ci2;
    double rest_len;
    double stiffness;
public:
    Spring(int ci1, int ci2, double rest_len, double stiffness): ci1(ci1), ci2(ci2), rest_len(rest_len), 
        stiffness(stiffness) {}
    int get_ci1();
    int get_ci2();
    double get_rest_len();
    double get_stiffness();
};
