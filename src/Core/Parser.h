#pragma once

struct Data;

constexpr const char* DATA_FILE_PATH = "data.toml";

class Parser
{
public:
    Parser() = delete;

    static Data* readData();
};
