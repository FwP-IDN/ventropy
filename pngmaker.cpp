#include <png.h>
#include <sstream>
#include "pngmaker.h"

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}
pixel_t;

/* A picture. */
    
typedef struct
{
    pixel_t *pixels;
    size_t width;
    size_t height;
}
bitmap_t;

static int pix (int value, int max)
{
    if (value < 0) {
        return 0;
    }
    return (int) (256.0 *((double) (value)/(double) max));
}

static pixel_t * pixel_at (bitmap_t * bitmap, int x, int y)
{
    return bitmap->pixels + bitmap->width * y + x;
}

PngMaker::PngMaker() : Logger("PngMaker")
{
    chart_height = 256;
    bar_height = 32;
}

void PngMaker::MakeImage(const std::vector<unsigned int> &features)
{
    uint16_t box_width = 0x8;
    uint16_t box_height = 0x8;
    uint16_t box_per_row = 0x20;
    logger->info("Make image");
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    int status = -1;
    int pixel_size = 3;
    int depth = 8;

    bitmap_t fruit;

    status = 0;

    /* Create an image. */

    fruit.width = 0x20*0x08;
    fruit.height = (features.size()/0x20 + 1)*0x8;

    fruit.pixels = (pixel_t *)calloc (fruit.width * fruit.height, sizeof (pixel_t));

    for (y = 0; y < fruit.height; y+=box_height) {
        for (x = 0; x < fruit.width; x+=box_width) {
            for (int u=0; u<box_width; u++){
                for (int v=0; v<box_width; v++){
                    pixel_t * pixel = pixel_at (& fruit, x+v, y+u);
                    pixel->red = pix (features[y*(box_per_row/box_width)+x/box_width]&0xff, 0xff);
                    pixel->green = pix (features[y*(box_per_row/box_width)+x/box_width]&0xff, 0xff);
                    pixel->blue = pix (features[y*(box_per_row/box_width)+x/box_width]&0xff, 0xff);
                }
            }
        }
    }
    
    logger->info("prepare image {0:s}", filename.c_str());
    fp = fopen (filename.c_str(), "wb");
    if (! fp) {
        return;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        return;
    }
    
    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        return;
    }
    
    /* Set up error handling. */

    if (setjmp (png_jmpbuf (png_ptr))) {
        return;
    }

    bitmap_t * bitmap = &fruit;
    
    /* Set image attributes. */

    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    /* Initialize rows of PNG. */

    row_pointers = (png_byte **)png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; y++) {
        png_byte *row = (png_byte *)png_malloc (png_ptr, sizeof (uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; x++) {
            pixel_t * pixel = pixel_at (bitmap, x, y);
            *row++ = pixel->red;
            *row++ = pixel->green;
            *row++ = pixel->blue;
        }
    }
    
    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;
    
    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }

    png_free (png_ptr, row_pointers);
    png_destroy_write_struct (&png_ptr, &info_ptr);
    fclose (fp);
    return;
}

void PngMaker::SetFilename(std::string _filename)
{
    std::stringstream ss;
    ss << _filename << ".png";
    filename = ss.str();
}

void PngMaker::WritePNGErrorHandler(png_structp png_ptr, png_const_charp msg)
{
  // Unused
  (void)png_ptr;

  // Write the error to stderr
  fprintf(stderr, "error: %s (PNG write)\n", msg);

  // "Eject! EJECT!"
  exit(1);
}