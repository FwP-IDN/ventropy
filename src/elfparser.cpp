#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fstream>
#include <elf.h>

#include "elfparser.h"

bool ElfParser::Load(const std::string & _filename){
    filename = _filename;
    std::ifstream f(filename, std::ios::binary);
    if (f.fail()) return false;
    
    //read elf header and check
    Elf32_Ehdr header;
    f.read((char *)&header, sizeof(header));
    return is_ELF(header);
}

bool ElfParser::is_ELF(Elf32_Ehdr eh)
{
	if(!strncmp((char*)eh.e_ident, "\177ELF", 4))
		return true;
    return false;
}

void ElfParser::FeatureExtract(){

}