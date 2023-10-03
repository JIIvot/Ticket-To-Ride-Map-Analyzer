#include <algorithm>

#include "ShortestPathLengthFinder.h"
#include "../Data.h"

uint32 ShortestPathLengthFinder::getShortestPathLength(uint32 startVertex, uint32 endVertex)
{
    m_wagonsCnt = 3e9;
    m_endVertex = endVertex;

    dfs(startVertex, 0, {startVertex});

    return m_wagonsCnt;
}

void ShortestPathLengthFinder::dfs(uint32 currentVertex, uint32 wagonsCnt, std::vector<uint32> path)
{
    if (currentVertex == m_endVertex)
    {
        m_wagonsCnt = std::min(m_wagonsCnt, wagonsCnt);
        return;
    }

    for (const auto neighbour : m_data->m_graph[currentVertex])
    {
        if (std::ranges::find(path, neighbour) != path.end())
            continue;

        const auto trackWagonsCnt = m_data->m_trackWagonsNum[{currentVertex, neighbour}];
        if (wagonsCnt + trackWagonsCnt > 45)
            continue;

        auto newPath = path;
        newPath.push_back(neighbour);

        dfs(neighbour, wagonsCnt + trackWagonsCnt, newPath);
    }
}
