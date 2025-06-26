#include "object/Player.hpp"
#include <iostream>

Player::Player()
{
    x = 320;
    y = 400;
    speed = 4.0f;
    slowSpeed = 2.0f;
}

void Player::handleInput(const Uint8 *keyState)
{
    isSlow = keyState[SDL_SCANCODE_LSHIFT];
    isShooting = keyState[SDL_SCANCODE_Z];

    float moveSpeed = isSlow ? slowSpeed : speed;

    if (keyState[SDL_SCANCODE_LEFT])
        x -= moveSpeed;
    if (keyState[SDL_SCANCODE_RIGHT])
        x += moveSpeed;
    if (keyState[SDL_SCANCODE_UP])
        y -= moveSpeed;
    if (keyState[SDL_SCANCODE_DOWN])
        y += moveSpeed;

    if (x < 0)
        x = 0;
    if (x > 640)
        x = 640;
    if (y < 0)
        y = 0;
    if (y > 480)
        y = 480;
}

void Player::onHit()
{
    if (invincible || lives <= 0)
        return;

    lives--;
    invincible = true;
    invincibleTimer = 120; // 2秒無敵
    std::cout << "hit!!" << std::endl;
    std::cout << lives << std::endl;
}

void Player::update()
{
    // 無敵時間処理
    if (invincible)
    {
        invincibleTimer--;
        if (invincibleTimer <= 0)
        {
            invincible = false;
        }
    }

    // 弾の発射
    if (isShooting && shootCooldown == 0)
    {
        bullets.emplace_back(x, y - size); // 中央から発射
        shootCooldown = 5;                 // 連射間隔（小さいほど高速連射）
    }
    if (shootCooldown > 0)
    {
        shootCooldown--;
    }

    // 弾の更新
    for (auto &b : bullets)
    {
        b.update();
    }

    // 弾の削除（画面外）
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                 [](const Bullet &b)
                                 { return b.isOffScreen(); }),
                  bullets.end());
}

void Player::draw(SDL_Renderer *renderer)
{
    // 自機本体
    SDL_Rect rect = {static_cast<int>(x - size), static_cast<int>(y - size), size * 2, size * 2};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    if (isSlow)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect center = {static_cast<int>(x - 1), static_cast<int>(y - 1), 2, 2};
        SDL_RenderFillRect(renderer, &center);
    }

    // 弾の描画
    for (auto &b : bullets)
    {
        b.draw(renderer);
    }
}

void Player::removeDeadBullets()
{
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),

                                 [](const Bullet &b)
                                 { return b.isDead(); }),
                  bullets.end());
}