#pragma once

class ScoreManager {
public:
    static ScoreManager &getInstance();

    void reset();
    void addScore(int value);
    int getScore() const;

private:
    ScoreManager() = default;
    int score = 0;
};
