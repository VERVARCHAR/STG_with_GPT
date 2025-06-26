#include "scene/TitleScene.hpp"
#include <iostream>

void TitleScene::update()
{
    std::cout << "Updating Title Scene...\n";
}

void TitleScene::draw(SDL_Renderer *renderer)
{
    // 何も描かない、デバッグ用表示は廃止
}
