#include "Config.hpp"
#include <fstream>
#include <iostream>



const char* ConfigNotFoundException::what() {
    return "Configuration option not found";
}

const char* InvalidConfigOptionException::what() {
    return "Configuration option invalid";
}

Config::Config (const char* _filename, const char* _standardConfigData)
:standardConfigData(_standardConfigData)
{
    read(_filename);
}

Config::~Config (){} 

std::string Config::getValueByKey(std::string key) {
    if(data.find(key) != data.end()) {
        return data[key];
    }
    ConfigNotFoundException e;
    throw e;
    return nullptr;
}

void Config::printAllData() {
    for(std::pair<std::string, std::string> p : data) {
        std::cout << p.first << ": " << p.second << std::endl;
    }
}

void Config::read(const char* filename) {
    std::string line;
    std::ifstream configFile;
    configFile.open(filename);
    while( std::getline(configFile, line) ) {
        std::istringstream is_line(line);
        std::string key;
        if( std::getline(is_line, key, '=') ) {
            std::string value;
            if( std::getline(is_line, value) ) 
                data.insert(std::pair<std::string, std::string>(key, value)); //store line
        }
    }
    configFile.close();
    this->filename = filename;
}

const char* Config::get_filename() {
    return this->filename;
}

void Config::writeConfig(const char* data) {
    std::ofstream configFile;
    configFile.open(this->filename, std::ofstream::trunc);
    configFile << data;
    configFile.close();
    read(this->filename);
}

bool Config::writeStandardConfig(bool promptUser) {
    if (promptUser) {
        std::string in;
        std::cout << "\nStandard Configuration:" << std::endl;
        std::cout << standardConfigData << std::endl;
        std::cout << "Create a standard config file and override the currently loaded file? (y/n): ";
        std::cin >> in;
        if(in.compare("y") != 0) {
            return false;
        }
    }
    writeConfig(this->standardConfigData);
    return true;
}