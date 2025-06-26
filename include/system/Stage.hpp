#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct EnemySpawnData
{
    int frame;
    float x, y;
    std::string type;
    bool isBoss = false;
    std::string pattern;
    float speed = 0.0f;
    float angle = 0.0f;
    int hp = 1;
    nlohmann::json params;
};

class Stage
{
public:
    void loadFromFile(const std::string &filename);
    const std::vector<EnemySpawnData> &getSpawnList() const;

private:
    std::vector<EnemySpawnData> spawnList;
};
