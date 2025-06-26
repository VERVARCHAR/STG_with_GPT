#pragma once
#include "scene/Scene.hpp"
#include "object/Player.hpp"
#include "object/Enemy.hpp"
#include <vector>

#include "system/StageLoader.hpp"
#include "object/EnemyBullet.hpp"

#include <SDL2/SDL_ttf.h>

class GameScene : public Scene
{
public:
    GameScene();  // ← コンストラクタ追加
    ~GameScene(); // ← デストラクタ追加
    void update() override;
    void draw(SDL_Renderer *renderer) override;
    int frameCounter = 0;
    StageLoader stage;
    size_t nextSpawnIndex = 0;
    float playerX() const { return player.getX(); }
    float playerY() const { return player.getY(); }
    std::vector<EnemyBullet> enemyBullets;
    bool playerDead = false;
    int score = 0;

private:
    Player player;
    std::vector<Enemy> enemies;
    int enemySpawnTimer = 0;

    TTF_Font *font = nullptr;
};
