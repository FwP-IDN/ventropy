#include <iostream>
#include <string>
#include <iostream>
#include <functional>
#include <string>
#include <tr1/unordered_map>
#include <stdexcept>

#include "imgfactory.h"
#include "pngmaker.h"

using std::tr1::hash;

std::shared_ptr<spdlog::logger> ImageFactory::logger = spdlog::stdout_color_mt("ImgFactory");

namespace detail
{
    constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
    {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
    }
}

constexpr std::uint32_t fnhash(char const* s, std::size_t count)
{
    return detail::fnv1a_32(s, count);
}

ImageFactory::ImageFactory()
: Logger("ImageFactory")
{
}

ImageFactory::~ImageFactory()
{
}

ImageMaker *ImageFactory::GetFactory(std::string image)
{   
    logger->info("GetFactory");
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