#ifndef IMAGEMAKER
#define IMAGEMAKER
#include <stdint.h>
#include <string>
#include <vector>

class ImageMaker{
public:
    virtual void SetFilename(std::string filename) = 0;
    virtual void MakeImage(const std::vector<unsigned int> &features) = 0;
};
#endif