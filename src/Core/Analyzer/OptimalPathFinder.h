#pragma once

#include <vector>

#include "../Data.h"

class OptimalPathFinder
{
public:
    OptimalPathFinder(Data* data)
        : m_data(data) {}

    const std::vector<uint32>& getOptimalPath(Route route);

private:
    Data* m_data = nullptr;

    // DFS variables
    std::vector<uint32> m_path;
    uint32 m_endVertex = -1;
    double m_optimality = -1;

    void dfs(uint32 currentVertex, uint32 wagonsCnt, uint32 movesCnt, uint32 scores, std::vector<uint32> path);
};
