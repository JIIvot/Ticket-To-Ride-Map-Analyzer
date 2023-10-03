#include "Analyzer.h"
#include "Data.h"
#include "Logger.h"

void Analyzer::initialize() {
    m_data = Parser::readData();
}

void Analyzer::start() {
    LOG_INFO("Analyzer started.");

    for (const auto [startID, endID, scores] : m_data->m_routes) {
        m_path = {};
        m_optimality = -1;
        m_endVertex = endID;

        const auto startCityName = m_data->m_cities[startID];
        const auto endCityName = m_data->m_cities[endID];

        LOG_WARN("Start: {0}, End: {1}, Path: ", startCityName, endCityName);

        dfs(startID, 0, 0, 0, {startID});

        for (const auto city : m_path) {
            const auto cityName = m_data->m_cities[city];
            LOG_INFO(cityName);
        }
    }

    LOG_INFO("Analyzer finished.");
}

void Analyzer::destroy() {
    delete m_data;
}

void Analyzer::dfs(uint32 currentVertex, uint32 wagonsCnt, uint32 movesCnt, uint32 scores, std::vector<uint32> path) {
    if (currentVertex == m_endVertex) {
        const auto currentOptimality = static_cast<double>(scores) / movesCnt;
        if (currentOptimality > m_optimality) {
            m_optimality = currentOptimality;
            m_path = path;
        }

        return;
    }

    for (const auto neighbour : m_data->m_graph[currentVertex]) {
        if (std::ranges::find(path, neighbour) != path.end())
            continue;

        const auto trackWagonsCnt = m_data->m_trackWagonsNum[{currentVertex, neighbour}];
        const auto newScores = scores + m_data->m_scoresTable[trackWagonsCnt - 1];

        if (trackWagonsCnt + wagonsCnt > 45)
            continue;

        auto newPath = path;
        newPath.push_back(neighbour);

        dfs(neighbour, wagonsCnt + trackWagonsCnt, movesCnt + 1, newScores, newPath);
    }
}
