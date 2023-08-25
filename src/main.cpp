#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.hpp"
#include "Config.hpp"
#include "ImageASCII.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  string configPath = "../rcs/config.txt";
  string imagePath;
  if(argc > 1) {
    imagePath = argv[1];
  } else {
    cout << "No path to image provided. Abort." << endl;
    return 1;
  }
  if(argc > 2) {
    configPath = argv[2];
  }

  Config cfg(configPath.c_str());
  cout << "= Config loaded =" << endl;
  cfg.printAllData();
  cout << endl;
  ImageASCII imageASCII(&cfg);
  string sinput_width;
  try {
    sinput_width = cfg.getValueByKey("newWidth");
  }
  catch (ConfigNotFoundException e) {
    cout << e.what() << ": " << cfg.get_filename() << endl;
    return 1;
  }
  
  int input_width = stoi(sinput_width);
  Image origin(imagePath.c_str());

  //resizing image
  int input_height = float(input_width) / float(origin.w) * origin.h;
  Image resized(input_width, input_height, origin.channels);
  origin.resize(resized.data, input_width, input_height);
  if(resized.channels < 3) {
    cout << "Image type is not supported!" << endl;
    return 1;
  }

  string result;
  try {
    result = imageASCII.convertImage(resized);
  }
  catch (InvalidConfigOptionException e) {
    cout << e.what() << endl;
    return 1;
  }
  
  
  //print result
  cout << "RESULT:\n" << result << endl;
  cout << "Writing HTML and CSS..." << endl;
  //write html and css files
  imageASCII.writeHTMLfile();
  imageASCII.writeCSSfile();
  cout << "Done!" << endl;

  return 0;
}
