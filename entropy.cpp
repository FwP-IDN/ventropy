#include <fstream>

#include "entropy.h"

Entropy::Entropy() : 
Logger("Entropy")
{
    chunkSize = 256;
}

Entropy::~Entropy()
{

}

std::vector<unsigned int> Entropy::Extract(const std::string & _filename)
{
    logger->info("Entropy extraction");

    size_t filesize = 0;
    char buffer[chunkSize];
    std::vector<unsigned int> entropy;

    std::ifstream f(_filename, std::ios::binary);

    if (f.fail())
    {
        logger->error("file not found");
        throw std::invalid_argument("file not found");
    }

    filesize = getFileSize(f);
    for (int i = 0; i < filesize - chunkSize; i += chunkSize)
    {
        f.read(buffer, chunkSize);

        double ent = getEntropy(buffer);
        ent /= chunkSize;
        ent = 1.0 - ent;
        ent *= ent; // Square scale
        ent *= 100.0;
        entropy.push_back((unsigned int)ent);
    }
    return entropy;
}

size_t Entropy::getFileSize(std::ifstream &file)
{
    file.seekg(0, file.end);
    size_t filesize = file.tellg();
    file.seekg(0, file.beg);
    return filesize;
}

double Entropy::getEntropy(const char *buffer)
{
    // Some variables
    int histo[256];
    int i;
    double entropy = 0.0;

    makeHistogram(buffer, histo);

    for (i = 0; i < 256; i++)
    {
        double pr = (double)histo[i] / chunkSize;
        entropy += pr * (double)histo[i];
    }

    return entropy;
}

void Entropy::makeHistogram(const char *buffer, int histo[256])
{
    memset(histo, 0, sizeof(int) * 256);
    for (int i = 0; i < chunkSize; i++)
        histo[(unsigned char)buffer[i]]++;
}