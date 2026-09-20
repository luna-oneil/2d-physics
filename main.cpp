#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "objects.hpp"

bool frame(SDL_Window *window, SDL_Renderer *renderer, Circle &circle);
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
    if (!SDL_CreateWindowAndRenderer("SDL3 Boilerplate", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Window/Renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // creates circle
    Circle circle = Circle(400, 300, 200, 200, 180, 80);
    // runs the frame()
    // while loop has no body because frame both modifies state and returns whether the window is open
    while (frame(window, renderer, circle));

    // destructions
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// returns whether the window should continue being visible
bool frame(SDL_Window *window, SDL_Renderer *renderer, Circle &circle) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // set return value to close window
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    // circle movement
    circle.update_coords(0, 0.1);
    // clearing screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // drawing circle
    draw_circle(renderer, circle);
    // Make frame visible
    SDL_RenderPresent(renderer);
    return true;
}

void draw_circle(SDL_Renderer *renderer, Circle &circle) {
    Coordinates center = circle.get_coords();
    std::cout << circle.get_coords().y << std::endl;
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