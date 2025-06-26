#include "object/Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x_, float y_) : x(x_), y(y_) {}

void Enemy::update(float playerX, float playerY)
{
    y += speed;

    if (fireCooldown <= 0)
    {
        float dx = playerX - x;
        float dy = playerY - y;
        float len = std::sqrt(dx * dx + dy * dy);
        if (len != 0)
        {
            dx /= len;
            dy /= len;
        }
        bullets.emplace_back(x, y, dx, dy);
        fireCooldown = 60; // 1秒ごとに発射
    }
    else
    {
        fireCooldown--;
    }

    for (auto &b : bullets)
    {
        b.update();
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const EnemyBullet &b)
                                 { return b.isOffScreen(); }),
                  bullets.end());
}

void Enemy::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 赤
    SDL_Rect rect = {static_cast<int>(x - size), static_cast<int>(y - size), size * 2, size * 2};
    SDL_RenderFillRect(renderer, &rect);
}

bool Enemy::isOffScreen() const
{
    return y - size > 480;
}

bool Enemy::checkCollision(float bulletX, float bulletY, float radius)
{
    float dx = x - bulletX;
    float dy = y - bulletY;
    float distSq = dx * dx + dy * dy;
    float range = size + radius;
    if (distSq < range * range)
    {
        dead = true;
        return true;
    }
    return false;
}

void Enemy::onHit()
{
    dead = true;
}

std::optional<EnemyBullet> Enemy::tryFire(float playerX, float playerY)
{
    if (fireCooldown <= 0)
    {
        float dx = playerX - x;
        float dy = playerY - y;
        float len = std::sqrt(dx * dx + dy * dy);
        if (len != 0)
        {
            dx /= len;
            dy /= len;
        }
        fireCooldown = 60;
        return EnemyBullet(x, y, dx, dy);
    }
    else
    {
        fireCooldown--;
        return std::nullopt;
    }
}
