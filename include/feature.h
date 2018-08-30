#ifndef FEATURE
#define FEATURE
#include <vector>
#include <string>
#include <stdint.h>
#include <stdint.h>
#include <stddef.h>

class Feature{
    public:
        virtual std::vector<unsigned int> Extract(const std::string & _filename) = 0;
        virtual void SetChunkSize(uint16_t size) = 0;
};
#endif
