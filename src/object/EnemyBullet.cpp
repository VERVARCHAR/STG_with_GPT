#include "object/EnemyBullet.hpp"

EnemyBullet::EnemyBullet(float x_, float y_, float vx_, float vy_)
    : x(x_), y(y_), vx(vx_), vy(vy_) {}

void EnemyBullet::update()
{
    x += vx * speed;
    y += vy * speed;
}

void EnemyBullet::draw(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // 黄色
    SDL_Rect rect = {
        static_cast<int>(x - radius),
        static_cast<int>(y - radius),
        static_cast<int>(radius * 2),
        static_cast<int>(radius * 2)};
    SDL_RenderFillRect(renderer, &rect);
}

bool EnemyBullet::isOffScreen() const
{
    return (x < -10 || x > 650 || y < -10 || y > 490);
}
