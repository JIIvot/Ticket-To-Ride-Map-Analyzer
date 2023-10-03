#pragma once

#include <vector>

#include "../Parser.h"
#include "../Types.h"

struct Route;
struct Data;
class OptimalPathFinder;
class MiddleVertexFinder;

class Analyzer
{
public:
    Analyzer();
    
    void initialize();
    void start();
    void destroy();

private:
    static Analyzer* s_instance;
    
    Data* m_data = nullptr;
    MiddleVertexFinder* m_middleVertexFinder = nullptr;

    std::vector<std::vector<uint32>> m_optimalPaths;

    void findAndPrintOptimalPaths() const;
    void findAndPrintMiddleVertex() const;

    static void processThread(Route route, uint32 routeID);
};
