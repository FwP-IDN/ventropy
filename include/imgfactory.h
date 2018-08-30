#ifndef IMAGEFATORY
#define IMAGEFATORY
#include <string>
#include "imgmaker.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class ImageFactory: protected Logger{
    public:
        ImageFactory();
        static ImageMaker* GetFactory(std::string img);
        ~ImageFactory();
    private:
        static std::shared_ptr<spdlog::logger> logger;
};
#endif