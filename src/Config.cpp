#include "Config.hpp"
#include <fstream>
#include <iostream>

Config::Config () {

}

Config::~Config (){

} 

std::string Config::getValueByKey(std::string key) {
    if(data.find(key) != data.end()) {
        return data[key];
    }
    return nullptr;
}

void Config::printAllData() {
    for(std::pair<std::string, std::string> p : data) {
        std::cout << p.first << " : " << p.second << std::endl;
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
}