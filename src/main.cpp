#include <iostream>
#include <fstream>

using namespace std;

int main() {

  /*ofstream create;

  create.open("origin.ppm");

  create << "P3 " << endl;
  create << "20 20 " << endl;
  create << "255 " << endl;

  for(int y = 0; y<20;y++){
    for(int x=0;x<20;x++) {
      create << x*y%255 << " " << x*y%255 << " " << x*y%255 << " " << endl;
    }
  }

  create.close();*/


  string result = "";
  string ascii = ":. ";
  int lenght_ascii = ascii.length();
  string type = "", width = "", height = "", maxVal = "";

  ifstream origin;
  origin.open("origin.ppm");

  // read head of file
  origin >> type;
  origin >> width;
  origin >> height;
  origin >> maxVal;

  int _width = stoi(width);

  // read body of file
  string r = "", g = "", b = "";
  int R, G, B;
  while(!origin.eof()){
    origin >> r;
    origin >> g;
    origin >> b;

    R = stoi(r);
    G = stoi(g);
    B = stoi(b);

    float brightness = R * 0.3 + G * 0.59 + B * 0.11;

    if(brightness < 255/3) {
      result.append(" ");
    } else if(brightness < 255/2) {
      result.append(".");
    } else if(brightness < 255/1) {
      result.append(":");
    }

    cout << _width << endl;
    if(result.length()%(_width+1) == 0) {
        result.append("\n");
    }

  }
  std::cout << result << endl;

  origin.close();
  return 0;
}
