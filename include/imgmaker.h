#ifndef IMAGEMAKER
#define IMAGEMAKER

#include <string>

class ImageMaker{
public:
    virtual void SetFilename(std::string filename) = 0;
    virtual void MakeImage() = 0;
};
#endif