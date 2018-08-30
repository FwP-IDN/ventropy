#include "elfparser.h"
#include "parserFacade.h"

const std::vector<std::shared_ptr<Parser>> ParserFacade::parsers({
    std::make_shared<ElfParser>()
});

void ParserFacade::Parse(const std::string & _filename){
    for(auto &p : parsers){
        if(p->Load(_filename)){
            p->FeatureExtract();
        }
    }
}