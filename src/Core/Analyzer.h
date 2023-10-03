#pragma once

#include <vector>

#include "Parser.h"
#include "Types.h"

struct Data;

class Analyzer {
public:
    void initialize();
    void start();
    void destroy();

private:
    Data* m_data = nullptr;

    // DFS variables
    std::vector<uint32> m_path;
    uint32 m_endVertex = -1;
    double m_optimality = -1;

    void dfs(uint32 currentVertex, uint32 wagonsCnt, uint32 movesCnt, uint32 scores, std::vector<uint32> path);
};
