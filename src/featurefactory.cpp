#include <iostream>
#include <string>
#include <iostream>
#include <functional>
#include <string>
#include <tr1/unordered_map>
#include <stdexcept>
#include "common.h"
#include "featurefactory.h"
#include "entropy.h"

using std::tr1::hash;

std::shared_ptr<spdlog::logger> FeatureFactory::logger = spdlog::stdout_color_mt("FeatureFactory");


FeatureFactory::FeatureFactory()
: Logger("FeatureFactory")
{
}

FeatureFactory::~FeatureFactory()
{
}

std::shared_ptr<Feature> FeatureFactory::GetFactory(std::string image)
{   
    logger->debug("GetFactory");
    std::uint32_t opt = detail::fnv1a_32(image.c_str(), image.length());
    logger->debug("opt {0:x}", opt);
    switch (opt)
    {
    case fnhash("entropy", 7):
        logger->debug("opt is entropy");
    default:
        return std::shared_ptr<Feature>(new Entropy());
        break;
    }
}