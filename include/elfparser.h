#include <string>
#include <elf.h>
#include "parser.h"

class ElfParser: public Parser{
    public:
        virtual bool Load(const std::string & _filename);
        virtual void FeatureExtract();
        bool is_ELF(Elf32_Ehdr eh);
    private:
        std::string filename;
};