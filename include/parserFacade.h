#ifndef PARSERFACACDE
#define PARSERFACACDE
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "parser.h"

class ParserFacade{
    public:
        static void Parse(const std::string & filename);
    private:
        const static std::vector<std::shared_ptr<Parser>> parsers;
};
#endif