#ifndef PNGMAKER
#define PNGMAKER

#include <fstream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "imgmaker.h"
#include "logger.h"

class PngMaker : public ImageMaker, protected Logger
{
  public:
    PngMaker();
    ~PngMaker();
    virtual void SetFilename(std::string filename);
    virtual void MakeImage();
  private:
    std::fstream f;
    std::string filename;
};

#endif