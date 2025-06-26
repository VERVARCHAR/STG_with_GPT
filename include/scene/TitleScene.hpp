#pragma once
#include "scene/Scene.hpp"

class TitleScene : public Scene
{
public:
    void update() override;
    void draw(SDL_Renderer *renderer) override;
};
