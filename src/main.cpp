#include <iostream>
#include <fstream>
#include <sstream>
#include "Image.h"

using namespace std;

int main() {

  // declaraion
  string ascii = " .,:;!?$#@";  // best
  int lenght_ascii = ascii.length();
  int brightness_steps = 255 / lenght_ascii;

  //User input
  string filename;
  cout << "Wie heißt die Datei?" << endl;
  cin >> filename;

  Image origin(filename.c_str());

  int input_width;
  cout << "Wie breit soll das Bild am Ende sein (Original:" << origin.w << "x" << origin.h << "):" << endl;
  cin >> input_width;

  int render_opt;
  cout << "Wie soll die Helligkeit eines Pixels ermittlet werden?" << endl
       << "(1) Leuchtdichte der RGB Werte (realistischer)" << endl
       << "(2) Durchschnitt der RGB Werte" << endl;
  cin >> render_opt;

  int brightness_boost;
  cout << "Helligkeitsmodifikator (Standard: 1):" << endl;
  cin >> brightness_boost;

  // resizing image
  int input_height = float(input_width) / float(origin.w) * origin.h;
  Image resized(input_width, input_height, origin.channels);
  origin.resize(resized.data, input_width, input_height);

  if(resized.channels < 3) {
    cout << "Image type is not supported!" << endl;
    return 1;
  }

  //loop through image
  string html_result = "&nbsp";
  string result = "\n";
  int count=0;
  for(int y=0; y < resized.h; ++y){
    for(int x = 0; x < resized.w; ++x){
      int rgb[4];
      for(int ch=0; ch < resized.channels; ++ch) {
        rgb[ch] = resized.data[count+ch];

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
      switch (render_opt) {
        case 1:
          brightness = R * 0.2126 + G * 0.7152 + B * 0.0722 * brightness_boost;
          break;
        case 2:
          brightness = (R+G+B)/3 * brightness_boost;
          break;
        default:
          cout << "Invalid Render Option!" << endl;
          return 0;
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

      if(result.length()%(resized.w+1) == 0) {
          result.append("\n");
          html_result.append("</br>");
      }

      count = count + resized.channels;
    }
  }


  cout << "RESULT:\n" << result << endl;

  cout << "Writing HTML and CSS..." << endl;
  // write html file
  ofstream html;
  html.open("HTML.html");

  html << "<html>" << endl
       << "<head>" << endl
       << "<link rel=\"stylesheet\" href=\"style.css\">" << endl
       << "</head>" << endl
       << "<body>" << endl
       << html_result << endl
       << "</body>" << endl
       << "</html>" << endl;

  html.close();


  // write css file
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
  cout << "Done!" << endl;

  return 0;
}
