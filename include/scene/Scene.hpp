#pragma once
#include <SDL2/SDL.h>

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer *renderer) = 0; // 引数追加
};
