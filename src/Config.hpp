#include <sstream>
#include <map>
#pragma once

class Config {
public:
    Config();
    ~Config();
    void read(const char* filename);
    std::string getValueByKey(std::string key);
    void printAllData();

private:
    std::map<std::string, std::string> data;
};