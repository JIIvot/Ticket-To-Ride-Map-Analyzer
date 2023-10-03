#include <spdlog/sinks/stdout_color_sinks.h>

#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_logger;

void Logger::initialize() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_logger = spdlog::stdout_color_mt("Analyzer");
    s_logger->set_level(spdlog::level::trace);
}
