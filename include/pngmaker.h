#ifndef PNGMAKER
#define PNGMAKER

#include <fstream>
#include <png.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "imgmaker.h"
#include "logger.h"

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

/* A picture. */

typedef struct
{
    pixel_t *pixels;
    size_t width;
    size_t height;
} bitmap_t;


class PngMaker : public ImageMaker, protected Logger
{
  public:
    PngMaker();
    ~PngMaker();
    virtual void SetFilename(std::string filename);
    virtual void MakeImage(const std::vector<unsigned int> &features);
    virtual void SetBlockSize(Block block);

    static void WritePNGErrorHandler(png_structp png_ptr, png_const_charp msg);
    static int  pix(uint16_t value, uint16_t max);
    static pixel_t *pixel_at(bitmap_t *bitmap, int x, int y);
  private:
    std::fstream f;
    std::string filename;
    uint32_t chart_height;
    uint32_t bar_height;
    uint16_t box_width;
    uint16_t box_height;
    uint16_t box_per_row;
};

#endif