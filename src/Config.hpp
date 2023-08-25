#include <sstream>
#include <map>
#pragma once

class ConfigNotFoundException: public std::exception {
public:
    const char* what();
};

class InvalidConfigOptionException: public std::exception {
public:
    const char* what();
};

class Config {
public:
    Config(const char* _filename, const char* _standardConfigData);
    ~Config();
    void read(const char* filename);
    std::string getValueByKey(std::string key);
    void printAllData();
    const char* get_filename();
    void writeConfig(const char* data);
    bool writeStandardConfig(bool promptUser);

private:
    const char* standardConfigData;
    const char* filename;
    std::map<std::string, std::string> data;
};