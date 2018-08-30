#ifndef IMAGEMAKER
#define IMAGEMAKER
#include <stdint.h>
#include <string>
#include <vector>
#include "common.h"

class ImageMaker{
public:
    virtual void SetFilename(std::string filename) = 0;
    virtual void MakeImage(const std::vector<unsigned int> &features) = 0;
    virtual void SetBlockSize(Block block) = 0;
};
#endif