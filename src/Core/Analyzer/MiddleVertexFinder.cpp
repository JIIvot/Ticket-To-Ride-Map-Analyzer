#include <algorithm>
#include <thread>

#include "MiddleVertexFinder.h"
#include "ShortestPathLengthFinder.h"
#include "../Logger.h"
#include "../Data.h"

MiddleVertexFinder* MiddleVertexFinder::s_instance;

MiddleVertexFinder::MiddleVertexFinder(Data* data)
    : m_data(data)
{
    m_shortestPathFinder = new ShortestPathLengthFinder(data);
    s_instance = this;
    m_graphSize = data->m_graph.size();
    m_longestDistanceFromVertex.resize(data->m_graph.size());
}

MiddleVertexFinder::~MiddleVertexFinder()
{
    delete m_shortestPathFinder;
}

uint32 MiddleVertexFinder::getMiddleVertex() const
{
    std::vector<std::thread*> threads(m_graphSize);
    for (uint32 i = 0; i < m_graphSize; ++i)
    {
        threads[i] = new std::thread(processThread, i);
    }

    for (const auto thread : threads)
    {
        thread->join();
        delete thread;
    }

    uint32 middleVertex = 0;
    uint32 middleVertexLongestDistance = 3e9;
    for (uint32 vertex = 0; vertex < m_graphSize; ++vertex)
    {
        const auto currentLongestDistance = m_longestDistanceFromVertex[vertex];
        if (currentLongestDistance < middleVertexLongestDistance)
        {
            middleVertexLongestDistance = currentLongestDistance;
            middleVertex = vertex;
        }
    }

    for (uint32 vertex = 0; vertex < m_graphSize; ++vertex)
        LOG_WARN("City: {0}, Longest distance: {1}", m_data->m_cities[vertex], m_longestDistanceFromVertex[vertex]);

    return middleVertex;
}

void MiddleVertexFinder::processThread(uint32 startVertex)
{
    auto* shortestPathLengthFinder = new ShortestPathLengthFinder(s_instance->m_data);

    uint32 longestDistance = 0;
    for (uint32 endVertex = 0; endVertex < s_instance->m_graphSize; ++endVertex)
    {
        if (endVertex == startVertex)
            continue;

        LOG_INFO("Processing Start: {0}, End: {1}", startVertex, endVertex);
        longestDistance = std::max(longestDistance, shortestPathLengthFinder->getShortestPathLength(startVertex, endVertex));
    }

    s_instance->m_longestDistanceFromVertex[startVertex] = longestDistance;

    delete shortestPathLengthFinder;
}
