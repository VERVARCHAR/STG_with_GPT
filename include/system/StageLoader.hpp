#pragma once
#include <vector>
#include <string>

struct SpawnInfo
{
    int frame;
    float x, y;
};

class StageLoader
{
public:
    bool loadFromFile(const std::string &filepath);
    const std::vector<SpawnInfo> &getSpawnList() const;

private:
    std::vector<SpawnInfo> spawnList;
};
