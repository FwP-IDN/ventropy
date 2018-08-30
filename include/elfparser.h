#include <string>

#include "parser.h"

class ElfParser: public Parser{
    public:
        virtual bool Load(const std::string & _filename);
        virtual void FeatureExtract();
    private:
        std::string filename;
};