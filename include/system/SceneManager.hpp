#pragma once
#include "scene/Scene.hpp"
#include <SDL2/SDL.h>

class SceneManager
{
public:
    static SceneManager &getInstance();

    void changeScene(Scene *scene);
    void update();
    void draw(SDL_Renderer *renderer); // 引数追加
    void cleanup();

private:
    SceneManager() = default;
    Scene *currentScene = nullptr;
};
