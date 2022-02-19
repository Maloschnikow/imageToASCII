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
  // brighness values from dark to bright @#W$9876543210?!abc;:+=-,_
  //string ascii = " _.,-=+:;!?018$W#@";
  string ascii = " .,:;!?$#@";  // best
  //string ascii = " .,:;";


  int lenght_ascii = ascii.length();
  int brightness_steps = 255 / lenght_ascii;
  string type = "", width = "", height = "", maxVal = "";

  ifstream origin;
  origin.open("sinon.ppm");

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

    //Luminace
    //float brightness = R * 0.3 + G * 0.59 + B * 0.11;

    // durchschnitt
    float brightness = (R + G + B) / 3;

    int right_char = brightness / brightness_steps;
    result = result + ascii[right_char];

    if(result.length()%(_width+1) == 0) {
        result.append("\n");
    }

  }
  std::cout << result << endl;

  origin.close();
  return 0;
}
