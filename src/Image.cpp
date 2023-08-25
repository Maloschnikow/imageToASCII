#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "Image.hpp"
#include "stb-master/stb_image.h"
#include "stb-master/stb_image_write.h"
#include "stb-master/stb_image_resize.h"
#include <fstream>

using namespace std;

Image::Image(const char* filename){
  if(read(filename)){
    cout << "Read " << filename << endl;
    size = w*h*channels;
  } else {
    cout << "Failed to Read " << filename << endl;
  }
}
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels){
  size = w*h*channels;
  data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
  memcpy(data, img.data, size);
}
Image::~Image(){
  stbi_image_free(data);
}

bool Image::read(const char* filename){
  data = stbi_load(filename, &w, &h, &channels, 0);
  return data != NULL;
}
bool Image::write(const char* filename) {
    ImageType type = getFileType(filename);
    int success;
    switch (type) {
      case PNG:
        success = stbi_write_png(filename, w, h, channels, data, w*channels);
        break;
      case JPG:
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;
      case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
      case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    }
  return success != 0;
}

bool Image::resize(uint8_t* data2, int out_w, int out_h) {
  int success = stbir_resize_uint8(data, w , h, 0, data2, out_w, out_h, 0, channels);
  return success != 0;
}

ImageType Image::getFileType(const char* filename) {
  const char * ext = strchr(filename, '.');
  if(ext != nullptr) {
    if(strcmp(ext, ".png") == 0) {
      return PNG;
    }
    else if(strcmp(ext, ".jpg")==0 || strcmp(ext, ".JPG")==0 || strcmp(ext, ".jpeg") == 0) {
      return JPG;
    } else if(strcmp(ext, ".bmp") == 0) {
      return BMP;
    } else if(strcmp(ext, ".tga") == 0) {
      return TGA;
    }

  }
  return PNG;
}