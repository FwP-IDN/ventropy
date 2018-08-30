#include <iostream>
#include <string>
#include <iostream>
#include <functional>
#include <string>
#include <tr1/unordered_map>
#include <stdexcept>
#include "common.h"
#include "imgfactory.h"
#include "pngmaker.h"

using std::tr1::hash;

std::shared_ptr<spdlog::logger> ImageFactory::logger = spdlog::stdout_color_mt("ImageFactory");

ImageFactory::ImageFactory()
: Logger("ImageFactory")
{
}

ImageFactory::~ImageFactory()
{
}

ImageMaker *ImageFactory::GetFactory(std::string image)
{   
    logger->debug("GetFactory");
    std::uint32_t opt = detail::fnv1a_32(image.c_str(), image.length());
    logger->debug("opt {0:x}", opt);
    switch (opt)
    {
    case fnhash("png", 3):
        logger->debug("opt is png");
    default:
        return new PngMaker();
        break;
    }
}