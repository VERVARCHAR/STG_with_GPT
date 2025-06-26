// src/system/Stage.cpp
#include "system/Stage.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool Stage::loadFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open stage file: " << filepath << "\n";
        return false;
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
    std::cout << "[DEBUG] stage loaded. enemy count: " << spawnList.size() << std::endl;

    return true;
}

const std::vector<EnemySpawnData> &Stage::getSpawnList() const
{
    return spawnList;
}
