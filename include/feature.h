#ifndef FEATURE
#define FEATURE
#include <vector>
#include <string>

class Feature{
    public:
        virtual std::vector<unsigned int> Extract(const std::string & _filename) = 0;
};
#endif
