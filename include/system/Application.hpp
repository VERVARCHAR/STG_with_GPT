#pragma once
#include <SDL2/SDL.h>

class Application
{
public:
    bool init();
    void run();
    void shutdown();

    SDL_Renderer *getRenderer() const { return renderer; }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    const int windowWidth = 800;
    const int windowHeight = 480;
};
