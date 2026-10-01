#pragma once

// infinite border spanning across the x or y axis

class Wall {
public:
    bool vertical;
    // if vertical, coordinate on the x axis, if horizontal, on the y axis
    double location;
    Wall(bool vertical, double location): vertical(vertical), location(location) {}
    Wall(): Wall(false, 0) {}
};
