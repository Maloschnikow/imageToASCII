#include <iostream>
#include <stdint.h>
#pragma once
enum ImageType {
  PNG,
  JPG,
  BMP,
  TGA
};



class Image {
public:
  uint8_t* data = NULL;
  size_t size = 0;
  int w;
  int h;
  int channels;

  Image(const char* filename);
  Image(int w, int h, int channels);
  Image(const Image& img);
  ~Image();

  bool read(const char* filename);
  bool write(const char* filename);
  bool resize(uint8_t* data2, int out_w, int out_h);

  ImageType getFileType(const char* filename);

private:
};
