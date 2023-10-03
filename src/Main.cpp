#include "Core/Logger.h"
#include "Core/Analyzer.h"
#include "Core/Types.h"

int32 main() {
    Logger::initialize();

    Analyzer analyzer;
    analyzer.initialize();
    analyzer.start();
    analyzer.destroy();

    system("pause");
    return 0;
}
