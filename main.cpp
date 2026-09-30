#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include <random>
#include "circle.hpp"

bool frame(SDL_Window *window, SDL_Renderer *renderer, std::vector<Circle> &circles);
void draw_circle(SDL_Renderer *renderer, Circle &circle);

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
    // initializes list of circles with one circle
    std::vector<Circle> circles;
    circles.push_back(Circle(400.0, 300.0, 100, 240, 230, 30));
    circles.push_back(Circle(500.0, 100.0, 50, 200, 20, 80));
    // runs the frame()
    // while loop has no body because frame both modifies state and returns whether the window is open
    while (frame(window, renderer, circles));

    // destructions
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// returns whether the window should continue being visible
bool frame(SDL_Window *window, SDL_Renderer *renderer, std::vector<Circle> &circles) {
    // setting up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(-0.001, 0.001);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // set return value to close window
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    // circle movement
    for (long long unsigned int i = 0; i < circles.size(); i++) {
        circles[i].accelerate(distrib(gen), distrib(gen));
        circles[i].move();
    }
    // clearing screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // drawing circle
    for (long long unsigned int i = 0; i < circles.size(); i++) {
        draw_circle(renderer, circles[i]);
    }
    // Make frame visible
    SDL_RenderPresent(renderer);
    // return and say the next frame should happen
    return true;
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
