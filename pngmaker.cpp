#include <png.h>
#include "pngmaker.h"

PngMaker::PngMaker(){
    logger = spdlog::stdout_color_mt("png");
}

void PngMaker::MakeImage(){
    logger->info("Make image");
}

void PngMaker::SetFilename(std::string _filename){
    filename = _filename;
}