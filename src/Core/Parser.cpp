#include <filesystem>
#include <toml/toml.hpp>

#include "Data.h"
#include "Parser.h"

Data* Parser::readData() {
    const auto dataFile = toml::parse(DATA_FILE_PATH);
    const auto data = new Data;

    data->m_scoresTable = toml::find<std::vector<uint32>>(dataFile, "scores");
    data->m_wagonsLimit = toml::find<uint32>(dataFile, "wagonsLimit");
    data->m_cities = toml::find<std::vector<std::string>>(dataFile, "cities");

    data->m_graph.resize(data->m_cities.size());

    for (int32 i = 0; i < data->m_cities.size(); ++i)
        data->m_citiesMap[data->m_cities[i]] = i;

    const auto routeStarts = toml::find<std::vector<std::string>>(dataFile, "routeStarts");
    const auto routeEnds = toml::find<std::vector<std::string>>(dataFile, "routeEnds");
    const auto routeScores = toml::find<std::vector<uint32>>(dataFile, "routeScores");

    for (int32 i = 0; i < routeStarts.size(); ++i)
        data->m_routes.push_back({data->m_citiesMap[routeStarts[i]], data->m_citiesMap[routeEnds[i]], routeScores[i]});

    const auto trackStarts = toml::find<std::vector<std::string>>(dataFile, "trackStarts");
    const auto trackEnds = toml::find<std::vector<std::string>>(dataFile, "trackEnds");
    const auto trackWagonsNum = toml::find<std::vector<uint32>>(dataFile, "trackWagonsNum");

    for (int32 i = 0; i < trackStarts.size(); ++i) {
        const auto trackStartID = data->m_citiesMap[trackStarts[i]];
        const auto trackEndID = data->m_citiesMap[trackEnds[i]];

        data->m_trackWagonsNum[{trackStartID, trackEndID}] = trackWagonsNum[i];
        data->m_trackWagonsNum[{trackEndID, trackStartID}] = trackWagonsNum[i];

        data->m_graph[trackStartID].push_back(trackEndID);
        data->m_graph[trackEndID].push_back(trackStartID);
    }

    return data;
}
