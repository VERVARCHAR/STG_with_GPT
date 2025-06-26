#include "system/StageLoader.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool StageLoader::loadFromFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open stage file: " << filepath << "\n";
        return false;
    }

    json data;
    file >> data;

    for (const auto &entry : data)
    {
        SpawnInfo info;
        info.frame = entry.at("frame").get<int>();
        info.x = entry.at("x").get<float>();
        info.y = entry.at("y").get<float>();
        spawnList.push_back(info);
    }

    return true;
}

const std::vector<SpawnInfo> &StageLoader::getSpawnList() const
{
    return spawnList;
}
