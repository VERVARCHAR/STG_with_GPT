#include "scene/GameScene.hpp"
#include <SDL2/SDL.h>
#include "system/ScoreManager.hpp"

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

    // 最初の1回だけステージを読み込む
    if (frameCounter == 0)
    {
        stage.loadFromFile("assets/stages/stage1.json");
    }

    // 敵の出現管理
    const auto &spawns = stage.getSpawnList();
    while (nextSpawnIndex < spawns.size() && spawns[nextSpawnIndex].frame == frameCounter)
    {
        enemies.emplace_back(spawns[nextSpawnIndex].x, spawns[nextSpawnIndex].y);
        nextSpawnIndex++;
    }

    frameCounter++;

    for (auto &e : enemies)
    {
        e.update(playerX(), playerY());
    }

    // 当たり判定：playerの弾 vs 敵
    const auto &bullets = player.getBullets();

    for (auto &e : enemies)
    {
        e.update(player.getX(), player.getY());

        if (auto b = e.tryFire(player.getX(), player.getY()))
        {
            enemyBullets.push_back(*b);
        }
    }

    for (auto &b : enemyBullets)
        b.update();
    enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                                      [](const EnemyBullet &b)
                                      { return b.isOffScreen(); }),
                       enemyBullets.end());

    // プレイヤー弾 vs 敵の当たり判定 + スコア加算
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
                bullet.setDead(); // 弾を無効化
                if (enemy.isDead())
                {
                    ScoreManager::getInstance().addScore(1000);
                }
            }
        }
    }

    player.removeDeadBullets(); // 死んだ弾を削除（player 側に必要）

    // 死亡・画面外の敵を削除
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
                player.onHit(); // 残機を減らして無敵に
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

    // あとで "SCORE: 000000", "POWER: ★★" なども追加可能
}

GameScene::~GameScene()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}