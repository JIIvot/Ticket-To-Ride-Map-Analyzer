#pragma once

#include <vector>

#include "../Types.h"

struct Data;

/* Path length = number of wagons */
class ShortestPathLengthFinder
{
public:
    ShortestPathLengthFinder(Data* data)
        : m_data(data) {}

    uint32 getShortestPathLength(uint32 startVertex, uint32 endVertex);

private:
    Data* m_data = nullptr;

    uint32 m_wagonsCnt = 3e9;
    uint32 m_endVertex = -1;

    void dfs(uint32 currentVertex, uint32 wagonsCnt, std::vector<uint32> path);
};
