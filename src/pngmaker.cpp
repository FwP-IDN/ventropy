#include <png.h>
#include <sstream>
#include "common.h"
#include "pngmaker.h"
#include "hsl2rgb.hpp"

int PngMaker::pix(uint16_t value, uint16_t max)
{
    return (int)(256.0 * ((double)(value) / (double)max));
}

pixel_t *PngMaker::pixel_at(bitmap_t *bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

static RGB rainbowIdx(uint16_t value){
    uint16_t hue = (uint16_t)(MAX_HUE * ((double)(value) / (double)MAX_HUE));
    HSL data = HSL(MAX_HUE - hue, 1.0f, 0.5f);
    return HSLToRGB(data);
}

PngMaker::PngMaker() : Logger("PngMaker")
{
    box_width = 0x8;
    box_height = 0x8;
    box_per_row = 0x20;
    chart_height = 256;
    bar_height = 32;
}

void PngMaker::SetBlockSize(Block block){
    box_width<<block;
    box_height<<block;
    box_per_row = 0x100/box_width;
}

void PngMaker::MakeImage(const std::vector<unsigned int> &features)
{
    logger->debug("Make image");
    FILE *fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte **row_pointers = NULL;
    int pixel_size = 3;
    int depth = 8;

    bitmap_t fruit;

    fruit.width = box_per_row * box_width;
    fruit.height = (features.size() / box_per_row + 1) * box_height;

    fruit.pixels = (pixel_t *)calloc(fruit.width * fruit.height, sizeof(pixel_t));

    for (y = 0; y < fruit.height; y += box_height)
    {
        for (x = 0; x < fruit.width; x += box_width)
        {
            uint16_t e = features[y * (box_per_row / box_width) + x / box_width];
            uint8_t start = 1;
            uint8_t end = box_width-1;
            RGB rgb = rainbowIdx(e);
            for (int u = start; u < end; u++)
            {
                for (int v = start; v < end; v++)
                {
                    pixel_t *pixel = pixel_at(&fruit, x + v, y + u);
                    pixel->red   = rgb.R;
                    pixel->green = rgb.G;
                    pixel->blue  = rgb.B;
                }
            }
        }
    }

    logger->debug("prepare image {0:s}", filename.c_str());
    fp = fopen(filename.c_str(), "wb");
    if (!fp)
    {
        throw vent_ex("png file error", errno);
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
        throw vent_ex("png create error", errno);
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        throw vent_ex("png create info struct error", errno);
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        throw vent_ex("png set jump error", errno);
    }

    bitmap_t *bitmap = &fruit;

    png_set_IHDR(png_ptr,
                 info_ptr,
                 bitmap->width,
                 bitmap->height,
                 depth,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    row_pointers = (png_byte **)png_malloc(png_ptr, bitmap->height * sizeof(png_byte *));
    for (y = 0; y < bitmap->height; y++)
    {
        png_byte *row = (png_byte *)png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; x++)
        {
            pixel_t *pixel = pixel_at(bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }

    png_init_io(png_ptr, fp);
    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (y = 0; y < bitmap->height; y++)
    {
        png_free(png_ptr, row_pointers[y]);
    }

    png_free(png_ptr, row_pointers);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return;
}

void PngMaker::SetFilename(std::string pfilename)
{
    //Get save image name
    size_t extension = pfilename.find_last_of(".");
    size_t last = pfilename.find_last_of("/");
    pfilename = pfilename.substr(last + 1, extension);
     
    std::stringstream ss;
    ss << pfilename << ".png";
    filename = ss.str();
}

void PngMaker::WritePNGErrorHandler(png_structp png_ptr, png_const_charp msg)
{
    (void)png_ptr;
    throw vent_ex("png write error", errno);
    return;
}