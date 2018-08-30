#ifndef ENTROPY
#define ENTROPY
#include <string>
#include "feature.h"
#include "logger.h"

class Entropy : public Feature, protected Logger
{
  public:
    Entropy();
    ~Entropy();
    void SetChunkSize(u_int16_t size) { chunkSize = size; }

    virtual std::vector<unsigned int> Extract(const std::string & _filename);

  private:
    uint16_t chunkSize;
    size_t getFileSize(std::ifstream &file);
    double getEntropy(const char *buffer);
    void makeHistogram(const char *buffer, int Array[256]);
};
#endif