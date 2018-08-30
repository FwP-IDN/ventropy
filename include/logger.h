#ifndef BASE
#define BASE
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Logger{
public:
    Logger();
    Logger(const char *);
    ~Logger();
protected:
    std::shared_ptr<spdlog::logger> logger;
};
#endif