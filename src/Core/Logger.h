#pragma once

#include <memory>
#include <spdlog/spdlog.h>

class Logger {
public:
    Logger() = delete;

    static void initialize();

    static std::shared_ptr<spdlog::logger>& getLogger() { return s_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

#define LOG_TRACE(...) Logger::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) Logger::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) Logger::getLogger()->critical(__VA_ARGS__)
