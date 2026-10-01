#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "circle.hpp"
#include "wall.hpp"

bool frame(SDL_Renderer *renderer, std::vector<Circle> &circles, std::vector<Wall> &walls);
void circle_movement(std::vector<Circle> &circles, std::vector<Wall> &walls);
void render(SDL_Renderer *renderer, std::vector<Circle> &circles);
void draw_circle(SDL_Renderer *renderer, Circle &circle);
double get_distance(const Vector2d &v1, const Vector2d &v2);
bool is_colliding(const Circle &c1, const Circle &c2);
bool is_colliding(const Circle &c, const Wall &w);

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize";
        return -1; 
    }

    // Create a window and a default renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!SDL_CreateWindowAndRenderer("SDL3 Boilerplate", 1000, 1000, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    // initializes list of circles with two circles
    std::vector<Circle> circles;
    circles.push_back(Circle(500.0, 100.0, 50, 200, 20, 80));
    circles.push_back(Circle(600.0, 100.0, 50, 200, 20, 80));
    circles.push_back(Circle(700.0, 100.0, 50, 200, 20, 80));
    circles.push_back(Circle(700.0, 200.0, 50, 200, 20, 80));
    circles.push_back(Circle(700.0, 800.0, 50, 200, 20, 80));
    circles.push_back(Circle(700.0, 600.0, 50, 200, 20, 80));
    // initalizes list of walls with 4 walls
    std::vector<Wall> walls;
    walls.push_back(Wall(true, 0));
    walls.push_back(Wall(false, 0));
    walls.push_back(Wall(false, 1000));
    walls.push_back(Wall(true, 1000));
    // runs the frame()
    // while loop has no body because frame both modifies state and returns whether the window is open
    while (frame(renderer, circles, walls));

    // destructions
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// returns whether the window should continue being visible
bool frame(SDL_Renderer *renderer, std::vector<Circle> &circles, std::vector<Wall> &walls) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // set return value to close window
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    // circle movement
    circle_movement(circles, walls);
    // rendering
    render(renderer, circles);
    // return and say the next frame should happen
    return true;
}

void circle_movement(std::vector<Circle> &circles, std::vector<Wall> &walls) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(-0.0025, 0.0025);
    for (long long unsigned int i = 0; i < circles.size(); i++) {
        circles[i].accelerate(distrib(gen), distrib(gen));
        circles[i].move();
        // collisions between circles (j = i + 1 to not check previous circles)
        for (long long unsigned int j = i + 1; j < circles.size(); j++) {
            if (is_colliding(circles[i], circles[j])) {
                circles[i].mirror_vel(true);
                circles[i].mirror_vel(false);
                circles[j].mirror_vel(false);
                circles[j].mirror_vel(true);
            }
        }
        // collisions between circles and walls
        for (long long unsigned int j = 0; j < walls.size(); j++) {
            if (!is_colliding(circles[i], walls[j])) {
                continue;
            }
            // mirrors across x axis if wall is vertical, across y axis if wall is horizontal
            circles[i].mirror_vel(!walls[j].vertical);
        }
    }
}

void render(SDL_Renderer *renderer, std::vector<Circle> &circles) {
    // clearing screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // drawing circle
    for (long long unsigned int i = 0; i < circles.size(); i++) {
        draw_circle(renderer, circles[i]);
    }
    // Make frame visible
    SDL_RenderPresent(renderer);
}

void draw_circle(SDL_Renderer *renderer, Circle &circle) {
    Vector2d center = circle.get_pos();
    SDL_Color color = circle.get_color();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int x = circle.get_radius();
    int y = 0;
    int p = 1 - circle.get_radius();

    while (y <= x) {
        SDL_RenderLine(renderer, center.x - x, center.y + y, center.x + x, center.y + y);
        SDL_RenderLine(renderer, center.x - x, center.y - y, center.x + x, center.y - y);
        SDL_RenderLine(renderer, center.x - y, center.y + x, center.x + y, center.y + x);
        SDL_RenderLine(renderer, center.x - y, center.y - x, center.x + y, center.y - x);

        y++;

        if (p <= 0) {
            p += 2 * y + 1;
        }
        else {
            x--;
            p += 2 * y - 2 * x + 1;
        }
    }
}

double get_distance(const Vector2d &v1, const Vector2d &v2) {
    return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
}

bool is_colliding(const Circle &c1, const Circle &c2) {
    return c1.get_radius() + c2.get_radius() >= get_distance(c1.get_pos(), c2.get_pos());
}

bool is_colliding(const Circle &c, const Wall &w) {
    if (w.vertical) {
        return c.get_radius() >= std::abs(c.get_pos().x - w.location);
    }
    return c.get_radius() >= std::abs(c.get_pos().y - w.location);
}
