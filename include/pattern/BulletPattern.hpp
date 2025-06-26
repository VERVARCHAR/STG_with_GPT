// include/pattern/BulletPattern.hpp
#pragma once

#include <optional>
#include "object/EnemyBullet.hpp"

class BulletPattern
{
public:
    virtual ~BulletPattern() = default;

    // 弾を撃つ処理：プレイヤー座標を使って弾の生成
    virtual std::optional<EnemyBullet> tryFire(float x, float y, float playerX, float playerY, int frame) = 0;
};
