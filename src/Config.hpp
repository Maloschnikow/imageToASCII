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
    Config(const char* filename);
    ~Config();
    void read(const char* filename);
    std::string getValueByKey(std::string key);
    void printAllData();
    const char* get_filename();

private:
    const char* filename;
    std::map<std::string, std::string> data;
};