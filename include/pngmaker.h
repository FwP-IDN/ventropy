#ifndef PNGMAKER
#define PNGMAKER

#include <fstream>
#include <png.h>
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
    virtual void MakeImage(const std::vector<unsigned int> &features);

    static void WritePNGErrorHandler(png_structp png_ptr, png_const_charp msg);
  private:
    std::fstream f;
    std::string filename;
    uint32_t chart_height;
    uint32_t bar_height;
};

#endif