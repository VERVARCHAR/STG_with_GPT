#include "system/Application.hpp"
#include "system/SceneManager.hpp"
#include "scene/TitleScene.hpp"
#include "scene/GameScene.hpp"
#include <iostream>

bool Application::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("Danmaku Game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << "\n";
        return false;
    }

    // SceneManager::getInstance().changeScene(new TitleScene());
    // 今はタイトル画面をスキップして、直接GameSceneへ
    SceneManager::getInstance().changeScene(new GameScene());
    return true;
}

void Application::run()
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        SceneManager::getInstance().update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SceneManager::getInstance().draw(renderer); // ← 修正

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
}

void Application::shutdown()
{
    SceneManager::getInstance().cleanup();
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
