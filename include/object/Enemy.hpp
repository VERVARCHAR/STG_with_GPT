#pragma once
#include <SDL2/SDL.h>
#include "object/EnemyBullet.hpp"
#include "system/Stage.hpp" // EnemySpawnData
#include <vector>
#include <algorithm>
#include <optional>

class Enemy
{
public:
    Enemy(const EnemySpawnData &data); // 新コンストラクタ

    void update(float playerX, float playerY);
    void draw(SDL_Renderer *renderer);

    bool checkCollision(float bulletX, float bulletY, float radius);

    bool isOffScreen() const;
    bool isBoss() const; // ← 敵がボスかどうか判定する関数（未定義なら定義する）
    bool isDead() const { return dead; }

    void onHit();

    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return size; }

    std::vector<EnemyBullet> bullets;
    int fireCooldown = 60;

    const std::vector<EnemyBullet> &getBullets() const { return bullets; }

    std::optional<EnemyBullet> tryFire(float playerX, float playerY);

    void onBombHit(float centerX, float centerY, float radius); // 範囲付きボム処理

    void takeDamage(int dmg); // ← ダメージを受ける処理（未定義なら定義する）
    void kill();              // ← 即死処理（未定義なら定義する）

private:
    float x, y;
    float speed = 2.0f;
    float angleDeg;
    int size = 10;
    int hp;
    bool dead = false;
    bool boss = false; // 仮にこのフラグでボスか判別するとする

    std::string type;
    std::string pattern;
    nlohmann::json params;
};
