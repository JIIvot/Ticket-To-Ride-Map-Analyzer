#include "OptimalPathFinder.h"

const std::vector<uint32>& OptimalPathFinder::getOptimalPath(Route route)
{
    m_path = {};
    m_optimality = -1;
    m_endVertex = route.m_endID;

    dfs(route.m_startID, 0, 0, 0, {route.m_startID});

    return m_path;
}

void OptimalPathFinder::dfs(uint32 currentVertex, uint32 wagonsCnt, uint32 movesCnt, uint32 scores, std::vector<uint32> path)
{
    if (currentVertex == m_endVertex)
    {
        const auto currentOptimality = static_cast<double>(scores) / movesCnt;
        if (currentOptimality > m_optimality)
        {
            m_optimality = currentOptimality;
            m_path = path;
        }

        return;
    }

    for (const auto neighbour : m_data->m_graph[currentVertex])
    {
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
