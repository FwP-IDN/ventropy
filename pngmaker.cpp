#include <png.h>
#include "pngmaker.h"

/*
file.seekg(0, file.end);
  s = file.tellg();
  file.seekg(0, file.beg);
  sz = s - SampleLength;
  width = s / SampleLength;
  printf("s:%d sz:%d width:%d\n", s, sz, width);
  all = new unsigned char[width * height * 3];
  raw = all;
*/
PngMaker::PngMaker() : Logger("PngMaker"){
}

void PngMaker::MakeImage(){
    logger->info("Make image");
}

void PngMaker::SetFilename(std::string _filename){
    filename = _filename;
}