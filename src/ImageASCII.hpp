#pragma once
#include "Image.hpp"
#include "Config.hpp"
#include <string>

class ImageASCII {
public:

    ImageASCII(Config* _config);

    void writeHTMLfile();
    void writeHTMLfile(const char* data);
    void writeCSSfile();
    std::string convertImage(Image &image);

    std::string asciiData;
    std::string htmlData;
    



private:
    Config* config;
};