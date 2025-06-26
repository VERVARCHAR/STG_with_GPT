// src/system/Stage.cpp
#include "system/Stage.hpp"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

void Stage::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Could not open stage file: " + filename);
    }

    json data;
    file >> data;
    spawnList.clear();

    for (const auto &e : data["enemies"])
    {
        EnemySpawnData enemy;
        enemy.frame = e.at("frame").get<int>();
        enemy.x = e.at("x").get<float>();
        enemy.y = e.at("y").get<float>();
        if (e.contains("type"))
            enemy.type = e["type"];
        if (e.contains("is_boss"))
            enemy.isBoss = e["is_boss"];
        if (e.contains("pattern"))
            enemy.pattern = e["pattern"];
        if (e.contains("speed"))
            enemy.speed = e["speed"];
        if (e.contains("angle"))
            enemy.angle = e["angle"];
        if (e.contains("hp"))
            enemy.hp = e["hp"];
        if (e.contains("params"))
            enemy.params = e["params"];

        spawnList.push_back(enemy);
    }
}

const std::vector<EnemySpawnData> &Stage::getSpawnList() const
{
    return spawnList;
}
