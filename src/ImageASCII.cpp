#include "ImageASCII.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ImageASCII::ImageASCII(Config* _config) : config(_config)
{}

void ImageASCII::writeHTMLfile(const char* data) {
  ofstream html;
  html.open("HTML.html");
  html << "<html>" << endl
       << "<head>" << endl
       << "<link rel=\"stylesheet\" href=\"style.css\">" << endl
       << "</head>" << endl
       << "<body>" << endl
       << data << endl
       << "</body>" << endl
       << "</html>" << endl;

  html.close();
}

void ImageASCII::writeHTMLfile() {
    writeHTMLfile(this->htmlData.c_str());
}

void ImageASCII::writeCSSfile() {
  ofstream css;
  css.open("style.css");
  css << "body {" << endl
      << "line-height: 6px;" << endl
      << "font-size: 9px;" << endl
      << "color: white;" << endl
      << "background-color: #000000;" << endl
      << "font-family: \"Consolas\";" << endl
      << "text-align: center;" << endl
      << "position: absolute;" << endl
      << "top: 50%;" << endl
      << "left: 50%;" << endl
      << "transform: translate(-50%, -50%);" << endl
      << "}" << endl;

  css.close();
}

std::string ImageASCII::convertImage(Image &image) {

    string ascii = " .,:;!?$#@";  // standard, but can be configured
    string sbrightnessType;
    string sbrightness_boost;
    string asciiSet;

    int brightnessType;
    int brightness_boost;

    sbrightnessType = config->getValueByKey("brightnessType");
    sbrightness_boost = config->getValueByKey("brightnessBoost");
    asciiSet = config->getValueByKey("ASCII");

    //check config and set values acordingly
    brightness_boost = stoi(sbrightness_boost);
    if (sbrightnessType.compare("LUMINANCE") == 0) { brightnessType = 1; }
    else if (sbrightnessType.compare("AVERAGE") == 0) { brightnessType = 2; }
    else { brightnessType = -1; }
    if (!asciiSet.empty() && asciiSet.size() >= 1) {
        ascii = asciiSet;
    }
    int lenght_ascii = ascii.length();
    int brightness_steps = 255 / lenght_ascii;

    //loop through image
    string html_result = "&nbsp";
    string result = "\n";
    int count=0;
    for(int y=0; y < image.h; ++y){
        for(int x = 0; x < image.w; ++x){
            int rgb[4];
            for(int ch=0; ch < image.channels; ++ch) {
                rgb[ch] = image.data[count+ch];
            }
            float R = rgb[0];
            float G = rgb[1];
            float B = rgb[2];
            stringstream sr;
            stringstream sg;
            stringstream sb;
            sr << R;
            sg << G;
            sb << B;
            string sR = sr.str();
            string sG = sg.str();
            string sB = sb.str();

            float brightness;
            switch (brightnessType) {
                case 1:
                brightness = R * 0.2126 + G * 0.7152 + B * 0.0722 * brightness_boost;
                break;
                case 2:
                brightness = (R+G+B)/3 * brightness_boost;
                break;
                default:
                cout << "Invalid Render Option!" << endl;
                return nullptr;
            }

            int right_char = brightness / brightness_steps -1;
            if(right_char <= 0) {
                result = result + ascii[0];
                html_result.append("&nbsp");
            } else if(right_char >= lenght_ascii) {
                result = result + ascii[lenght_ascii -1];
                html_result = html_result + "<dif style=\"color: rgb(" + sR + "," + sG + "," + sB +");\">" + ascii[lenght_ascii-1] + "</dif>";
            } else {
                result = result + ascii[right_char];
                html_result = html_result + "<dif style=\"color: rgb(" + sR + "," + sG + "," + sB +");\">" + ascii[right_char] + "</dif>";
            }

            if(result.length()%(image.w+1) == 0) {
                result.append("\n");
                html_result.append("</br>");
            }
            count = count + image.channels;
        }
    }
    this->asciiData = result;
    this->htmlData = html_result;
    return result;
}