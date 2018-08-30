#include <string>

#include "elfparser.h"

bool ElfParser::Load(const std::string & _filename){
    filename = _filename;
    return true;
}

void ElfParser::FeatureExtract(){

}