// GameScene.cpp
#include "scene/GameScene.hpp"
#include <SDL2/SDL.h>
#include "system/ScoreManager.hpp"
#include "system/Stage.hpp"

using namespace std;

const float BOMB_RADIUS = 150.0f;

void drawText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, int x, int y)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

GameScene::GameScene()
{
    if (TTF_Init() < 0)
    {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
    }

    font = TTF_OpenFont("assets/fonts/Mplus1-Black.ttf", 18);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    ScoreManager::getInstance().reset();
}

void GameScene::update()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    player.handleInput(keyState);
    player.update();

    // --- ボム効果処理（敵弾全削除＋敵への効果） ---
    if (player.isBombing())
    {
        // 敵弾すべて削除
        enemyBullets.clear();
        // 一定範囲内の敵にダメージ
        float px = player.getX();
        float py = player.getY();

        // 敵にボムダメージ（onBombHit() が定義されている必要あり）
        for (auto &enemy : enemies)
        {
            if (!enemy.isOffScreen())
            {
                enemy.onBombHit(px, py, BOMB_RADIUS);
            }
        }
    }

    // ステージデータ初期化（1回だけ）
    if (frameCounter == 0)
    {
        stage.loadFromFile("assets/stages/stage1.json");
    }

    const auto &spawns = stage.getSpawnList();
    while (nextSpawnIndex < spawns.size() && spawns[nextSpawnIndex].frame == frameCounter)
    {
        std::cout << "[DEBUG] enemy spawning at frame " << frameCounter << std::endl;
        enemies.emplace_back(spawns[nextSpawnIndex]);
        nextSpawnIndex++;
    }

    frameCounter++;

    for (auto &e : enemies)
    {
        e.update(player.getX(), player.getY());

        if (auto bullet = e.tryFire(player.getX(), player.getY(), frameCounter))
        {
            enemyBullets.push_back(*bullet);
        }
    }

    for (auto &b : enemyBullets)
        b.update();

    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                                      [](const EnemyBullet &b)
                                      { return b.isOffScreen(); }),
                       enemyBullets.end());

    auto &bullets = player.getBullets();

    for (auto &bullet : bullets)
    {
        for (auto &enemy : enemies)
        {
            float dx = bullet.getX() - enemy.getX();
            float dy = bullet.getY() - enemy.getY();
            float distSq = dx * dx + dy * dy;
            float sumRadius = bullet.getRadius() + enemy.getRadius();
            if (distSq < sumRadius * sumRadius)
            {
                enemy.onHit();
                bullet.setDead();
                if (enemy.isDead())
                {
                    ScoreManager::getInstance().addScore(1000);
                }
            }
        }
    }

    player.removeDeadBullets();

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const Enemy &e)
                                 { return e.isDead() || e.isOffScreen(); }),
                  enemies.end());

    if (!player.isInvincible())
    {
        for (const auto &b : enemyBullets)
        {
            float dx = b.getX() - player.getHitboxX();
            float dy = b.getY() - player.getHitboxY();
            float distSq = dx * dx + dy * dy;
            float sumRadius = b.getRadius() + player.getHitboxRadius();
            if (distSq < sumRadius * sumRadius)
            {
                player.onHit();
                break;
            }
        }
    }
}

void GameScene::draw(SDL_Renderer *renderer)
{
    for (auto &e : enemies)
        e.draw(renderer);
    for (auto &b : enemyBullets)
        b.draw(renderer);

    if (player.isBombing())
    {
        // 画面全体薄い青 + ボム範囲のサークルを描画
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 60);
        SDL_Rect overlay = {0, 0, 640, 480};
        SDL_RenderFillRect(renderer, &overlay);

        // 中心円を描画（半透明）
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 180);
        int centerX = static_cast<int>(player.getX());
        int centerY = static_cast<int>(player.getY());
        int radius = static_cast<int>(BOMB_RADIUS);

        // 簡易的な filled circle（SDLには標準関数がないため Bresenham 法的な円近似）
        for (int w = 0; w < radius * 2; w++)
        {
            for (int h = 0; h < radius * 2; h++)
            {
                int dx = radius - w;
                int dy = radius - h;
                if ((dx * dx + dy * dy) <= (radius * radius))
                {
                    SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
                }
            }
        }
    }

    player.draw(renderer);

    if (player.isDead())
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
        SDL_Rect overlay = {0, 0, 640, 480};
        SDL_RenderFillRect(renderer, &overlay);
        drawText(renderer, font, "GAME OVER", 260, 220);
        drawText(renderer, font,
                 "FINAL SCORE: " + std::to_string(ScoreManager::getInstance().getScore()),
                 200, 260);
    }

    drawText(renderer, font, "LIVES: " + std::to_string(player.getLives()), 10, 10);
    drawText(renderer, font,
             "SCORE: " + std::to_string(ScoreManager::getInstance().getScore()), 10, 30);
    drawText(renderer, font, "BOMBS: " + std::to_string(player.getBombs()), 10, 50);
    drawText(renderer, font, "FRAME " + std::to_string(frameCounter), 420, 420);
}

GameScene::~GameScene()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}
