#pragma once

#include <vector>

#include "../Types.h"

struct Data;
class ShortestPathLengthFinder;

class MiddleVertexFinder
{
public:
    MiddleVertexFinder(Data* data);
    ~MiddleVertexFinder();

    uint32 getMiddleVertex() const;

private:
    static MiddleVertexFinder* s_instance;

    Data* m_data = nullptr;
    ShortestPathLengthFinder* m_shortestPathFinder = nullptr;

    uint32 m_graphSize;
    std::vector<uint32> m_longestDistanceFromVertex;

    static void processThread(uint32 startVertex);
};
