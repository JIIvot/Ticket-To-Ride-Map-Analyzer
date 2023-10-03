#include "Analyzer.h"
#include "OptimalPathFinder.h"
#include "MiddleVertexFinder.h"
#include "../Data.h"
#include "../Logger.h"

Analyzer* Analyzer::s_instance;

Analyzer::Analyzer()
{
    s_instance = this;
}

void Analyzer::initialize()
{
    m_data = Parser::readData();

    m_optimalPaths.resize(m_data->m_routes.size());
    m_middleVertexFinder = new MiddleVertexFinder(m_data);
}

void Analyzer::start()
{
    LOG_INFO("Analyzer started.");

    findAndPrintOptimalPaths();
    findAndPrintMiddleVertex();

    LOG_INFO("Analyzer finished.");
}

void Analyzer::destroy()
{
    delete m_data;
    delete m_middleVertexFinder;
}

void Analyzer::findAndPrintOptimalPaths() const
{
    LOG_ERROR("Looking for optimal paths...");

    const auto routesNum = m_data->m_routes.size();
    std::vector<std::thread*> threads(routesNum);

    for (uint32 i = 0; i < routesNum; ++i)
        threads[i] = new std::thread(processThread, m_data->m_routes[i], i);

    for (const auto thread : threads)
    {
        thread->join();
        delete thread;
    }

    for (uint32 i = 0; i < routesNum; ++i)
    {
        const auto currentRoute = m_data->m_routes[i];

        LOG_WARN("Start: {0}, End: {1}, Path:", m_data->m_cities[currentRoute.m_startID], m_data->m_cities[currentRoute.m_endID]);
        for (const auto city : m_optimalPaths[i])
            LOG_INFO(m_data->m_cities[city]);
    }
}

void Analyzer::findAndPrintMiddleVertex() const
{
    LOG_ERROR("Looking for middle vertex...");
    LOG_WARN("Middle city: {}", m_data->m_cities[m_middleVertexFinder->getMiddleVertex()]);
}

void Analyzer::processThread(Route route, uint32 routeID)
{
    auto* optimalPathFinder = new OptimalPathFinder(s_instance->m_data);
    s_instance->m_optimalPaths[routeID] = optimalPathFinder->getOptimalPath(route);

    delete optimalPathFinder;
}
