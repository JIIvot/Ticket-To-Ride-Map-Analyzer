#pragma once

#include <vector>
#include <map>
#include <string>

#include "Types.h"

struct Route
{
    uint32 m_startID;
    uint32 m_endID;
    uint32 m_scores;
};

struct Data
{
    uint32 m_wagonsLimit;
    std::vector<std::string> m_cities;
    std::map<std::string, uint32> m_citiesMap;
    std::map<std::pair<uint32, uint32>, uint32> m_trackWagonsNum;
    std::vector<uint32> m_scoresTable;
    std::vector<Route> m_routes;
    std::vector<std::vector<uint32>> m_graph;
};
