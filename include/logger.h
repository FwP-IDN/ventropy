#ifndef BASE
#define BASE
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Logger{
public:
    Logger(const char *);
    ~Logger();
protected:
    std::shared_ptr<spdlog::logger> logger;
private:
    Logger();
};
#endif