#ifndef FEATUREFATORY
#define FEATUREFATORY

#include <string>
#include "feature.h"
#include "logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class FeatureFactory : public Logger 
{
    public:
        FeatureFactory();
        static std::shared_ptr<Feature> GetFactory(std::string image);
        ~FeatureFactory();
    private:
        static std::shared_ptr<spdlog::logger> logger;
};

#endif