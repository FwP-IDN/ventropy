#ifndef PARSER
#define PARSER
#include <string>

class Parser{
    public:
        virtual bool Load(const std::string & _filename) = 0;
        virtual void FeatureExtract() = 0;
};
#endif