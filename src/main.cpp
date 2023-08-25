#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "Config.hpp"
#include "ImageASCII.hpp"

using namespace std;

int main() {

  Config cfg("../rcs/config.txt");
  cout << "= Config loaded =" << endl;
  cfg.printAllData();
  cout << endl;

  ImageASCII imageASCII(&cfg);

  string sinput_width = cfg.getValueByKey("newWidth");
  int input_width = stoi(sinput_width);

  //User input
  string filename;
  cout << "Image filename: " << endl;
  cin >> filename;
  
  Image origin(filename.c_str());

  //resizing image
  int input_height = float(input_width) / float(origin.w) * origin.h;
  Image resized(input_width, input_height, origin.channels);
  origin.resize(resized.data, input_width, input_height);
  if(resized.channels < 3) {
    cout << "Image type is not supported!" << endl;
    return 1;
  }

  string result = imageASCII.convertImage(resized);
  
  //print result
  cout << "RESULT:\n" << result << endl;
  cout << "Writing HTML and CSS..." << endl;
  //write html and css files
  imageASCII.writeHTMLfile();
  imageASCII.writeCSSfile();
  cout << "Done!" << endl;

  return 0;
}
