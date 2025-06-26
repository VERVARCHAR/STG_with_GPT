#pragma once
#include "scene/Scene.hpp"
#include "object/Player.hpp"
#include "object/Enemy.hpp"
#include <vector>
#include <iostream>

// #include "system/StageLoader.hpp"
#include "object/EnemyBullet.hpp"
#include "system/Stage.hpp" // ← ヘッダ冒頭に必要

#include <SDL2/SDL_ttf.h>

class GameScene : public Scene
{
public:
    GameScene();  // ← コンストラクタ追加
    ~GameScene(); // ← デストラクタ追加
    void update() override;
    void draw(SDL_Renderer *renderer) override;
    int frameCounter = 0;
    // Stage stage;
    size_t nextSpawnIndex = 0;
    float playerX() const { return player.getX(); }
    float playerY() const { return player.getY(); }
    std::vector<EnemyBullet> enemyBullets;

private:
    TTF_Font *font = nullptr;
    Player player;
    std::vector<Enemy> enemies;
    // std::vector<EnemyBullet> enemyBullets;
    // int frameCounter = 0;
    // int nextSpawnIndex = 0;

    Stage stage; // ← これを追加！！！
};
