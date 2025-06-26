#pragma once
#include <SDL2/SDL.h>

class EnemyBullet
{
public:
    EnemyBullet(float x, float y, float vx, float vy);

    void update();
    void draw(SDL_Renderer *renderer) const;

    bool isOffScreen() const;
    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return radius; }
    void setDead();
    bool isDead() const;

private:
    float x, y;
    float vx, vy;
    float speed = 3.0f;
    float radius = 4.0f;
    bool dead = false;
};
