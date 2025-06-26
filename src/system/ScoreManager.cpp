#include "system/ScoreManager.hpp"

ScoreManager &ScoreManager::getInstance()
{
    static ScoreManager instance;
    return instance;
}

void ScoreManager::reset()
{
    score = 0;
}

void ScoreManager::addScore(int value)
{
    score += value;
}

int ScoreManager::getScore() const
{
    return score;
}
