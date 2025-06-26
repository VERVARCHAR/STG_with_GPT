#include "object/Enemy.hpp"
#include <cmath>

Enemy::Enemy(const EnemySpawnData &data)
{
    x = data.x;
    y = data.y;
    speed = data.speed;
    angleDeg = data.angle;
    hp = data.hp;
    boss = data.isBoss;
    type = data.type;
    pattern = data.pattern;
    params = data.params;
}

void Enemy::update(float playerX, float playerY)
{
    if (pattern == "straight")
    {
        float rad = angleDeg * M_PI / 180.0f;
        x += std::cos(rad) * speed;
        y += std::sin(rad) * speed;
    }
    else if (pattern == "sine")
    {
        float baseSpeed = speed;
        float rad = angleDeg * M_PI / 180.0f;
        float freq = params.value("frequency", 0.05f);
        float amp = params.value("amplitude", 30.0f);
        float offset = std::sin(y * freq) * amp;

        x += offset * 0.1f;
        y += std::sin(rad) * baseSpeed;
    }

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

void Enemy::onBombHit(float centerX, float centerY, float radius)
{
    float dx = getX() - centerX;
    float dy = getY() - centerY;
    float distSq = dx * dx + dy * dy;
    float radiusSq = radius * radius;

    if (distSq <= radiusSq)
    {
        if (isBoss())
            takeDamage(1);
        else
            kill();
    }
}

bool Enemy::isBoss() const
{
    return boss;
}

void Enemy::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp <= 0)
    {
        kill();
    }
}

void Enemy::kill()
{
    dead = true;
}
