#pragma once
#include <SDL2/SDL.h>

class Bullet
{
public:
    Bullet(float x, float y);

    void update();
    void draw(SDL_Renderer *renderer);
    bool isOffScreen() const;
    void setDead();
    bool isDead() const;
    float getX() const { return x; }
    float getY() const { return y; }
    float getRadius() const { return radius; }

private:
    float x, y;
    float speed = 8.0f;
    int radius = 3;
    bool dead = false;
};
