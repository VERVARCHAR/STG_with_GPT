// src/pattern/StraightShotPattern.cpp
#include "pattern/StraightShotPattern.hpp"
#include <cmath>

StraightShotPattern::StraightShotPattern(const nlohmann::json &params)
{
    if (params.contains("shoot_interval"))
        interval = params["shoot_interval"];
    if (params.contains("bullet_speed"))
        speed = params["bullet_speed"];
}

std::optional<EnemyBullet> StraightShotPattern::tryFire(float x, float y, float playerX, float playerY, int frame)
{
    if ((frame - lastFireFrame) < interval)
        return std::nullopt;

    lastFireFrame = frame;

    float dx = playerX - x;
    float dy = playerY - y;
    float angle = std::atan2(dy, dx);

    float vx = std::cos(angle) * speed;
    float vy = std::sin(angle) * speed;

    return EnemyBullet(x, y, vx, vy);
}
