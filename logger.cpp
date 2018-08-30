#include "logger.h"
#include <stdio.h>
Logger::Logger()
{
    printf("%s\n", typeid(this).name());
    logger = spdlog::stdout_color_mt(typeid(this).name());
}

Logger::Logger(const char * name)
{
    logger = spdlog::stdout_color_mt(name);
}

Logger::~Logger()
{

}