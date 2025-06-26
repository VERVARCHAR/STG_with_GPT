#pragma once
#include <SDL2/SDL.h>
#include "object/EnemyBullet.hpp"
#include <vector>
#include <algorithm>
#include <optional>

class Enemy
{
public:
    Enemy(float x, float y);
    void update();
    void draw(SDL_Renderer *renderer);
    bool isOffScreen() const;
    bool checkCollision(float bulletX, float bulletY, float radius);

    bool isDead() const { return dead; }

    std::vector<EnemyBullet> bullets;
    int fireCooldown = 60;

    void update(float playerX, float playerY);
    const std::vector<EnemyBullet> &getBullets() const { return bullets; }

    std::optional<EnemyBullet> tryFire(float playerX, float playerY);

private:
    float x, y;
    float speed = 2.0f;
    int size = 10;
    bool dead = false;
};
