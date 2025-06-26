#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "object/Bullet.hpp"

class Player
{
public:
    Player();
    void handleInput(const Uint8 *keyState);
    void update();
    void draw(SDL_Renderer *renderer);
    std::vector<Bullet> &getBullets() { return bullets; }
    const std::vector<Bullet> &getBullets() const { return bullets; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getHitboxX() const { return x; }
    float getHitboxY() const { return y; }
    float getHitboxRadius() const { return 3.0f; } // 東方風に中心点だけ判定

    int lives = 3;
    bool invincible = false;
    int invincibleTimer = 0;

    void onHit(); // 被弾処理
    bool isDead() const { return lives <= 0; }
    bool isInvincible() const { return invincible; }
    int getLives() const { return lives; }

    void removeDeadBullets();

private:
    float x,
        y;
    float speed;
    float slowSpeed;
    int size = 4;
    bool isSlow = false;

    std::vector<Bullet> bullets;
    bool isShooting = false;
    int shootCooldown = 0;
};
