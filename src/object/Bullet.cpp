#include "object/Bullet.hpp"

Bullet::Bullet(float x_, float y_) : x(x_), y(y_) {}

void Bullet::update()
{
    y -= speed;
}

void Bullet::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // 水色
    SDL_Rect rect = {static_cast<int>(x - radius), static_cast<int>(y - radius), radius * 2, radius * 2};
    SDL_RenderFillRect(renderer, &rect);
}

bool Bullet::isOffScreen() const
{
    return y + radius < 0;
}
