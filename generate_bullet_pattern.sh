#!/bin/bash

mkdir -p include/pattern
mkdir -p src/pattern

# BulletPattern.hpp
cat <<EOF > include/pattern/BulletPattern.hpp
#pragma once

#include <optional>
#include "object/EnemyBullet.hpp"

class BulletPattern {
public:
    virtual ~BulletPattern() = default;
    virtual std::optional<EnemyBullet> tryFire(float x, float y, float playerX, float playerY, int frame) = 0;
};
EOF

# StraightShotPattern.hpp
cat <<EOF > include/pattern/StraightShotPattern.hpp
#pragma once

#include "pattern/BulletPattern.hpp"
#include <nlohmann/json.hpp>

class StraightShotPattern : public BulletPattern {
public:
    StraightShotPattern(const nlohmann::json& params);
    std::optional<EnemyBullet> tryFire(float x, float y, float playerX, float playerY, int frame) override;

private:
    int interval = 60;
    float speed = 2.0f;
    int lastFireFrame = -9999;
};
EOF

# StraightShotPattern.cpp
cat <<EOF > src/pattern/StraightShotPattern.cpp
#include "pattern/StraightShotPattern.hpp"
#include <cmath>

StraightShotPattern::StraightShotPattern(const nlohmann::json& params)
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
EOF

echo "✔ BulletPattern と StraightShotPattern のファイルを作成しました！"
