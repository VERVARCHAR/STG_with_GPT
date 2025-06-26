// include/pattern/StraightShotPattern.hpp
#pragma once

#include "pattern/BulletPattern.hpp"
#include <nlohmann/json.hpp>

class StraightShotPattern : public BulletPattern
{
public:
    StraightShotPattern(const nlohmann::json &params);

    std::optional<EnemyBullet> tryFire(float x, float y, float playerX, float playerY, int frame) override;

private:
    int interval = 60;
    float speed = 2.0f;
    int lastFireFrame = -9999;
};
