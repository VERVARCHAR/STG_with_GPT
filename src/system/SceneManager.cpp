#include "system/SceneManager.hpp"
#include <iostream>

SceneManager &SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::changeScene(Scene *scene)
{
    if (currentScene)
        delete currentScene;
    currentScene = scene;
}

void SceneManager::update()
{
    if (currentScene)
        currentScene->update();
}

void SceneManager::draw(SDL_Renderer *renderer)
{
    if (currentScene)
        currentScene->draw(renderer);
}

void SceneManager::cleanup()
{
    if (currentScene)
    {
        delete currentScene;
        currentScene = nullptr;
    }
}
