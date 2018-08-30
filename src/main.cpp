// Includes
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "entropy.h"
#include "CLI11.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <elf.h>
#endif
#include "common.h"
#include "imgfactory.h"
#include "featurefactory.h"

using namespace std;

#define CHART_HEIGHT 480
#define BAR_HEIGHT 20

int main(int argc, char **argv)
{
  CLI::App app{"Vent v.0.1, an entropy level measurement tool for ELF"};

  std::string filename = "";
  app.add_option("-f,--file", filename, "file for information visualization")
    ->required()
    ->check(CLI::ExistingFile);
  std::string graphic = "png";
  app.add_option("-o,--output", graphic, "output graphic format, default is png");
  std::string info = "entropy";
  app.add_option("-i,--info", graphic, "information extraction method, default is entropy");
  Block block = Block::b8;
  app.add_set("-b,--block", block, {Block::b8, Block::b16, Block::b32}, "Image block size")
    ->type_name("enum/Block in {b8=8, b16=16, b32=32}");
  SampleBlock sample = SampleBlock::b256;
  app.add_option("-s, --sample", sample, "Sample block size")
    ->type_name("enum/SampleBlock in {b64=64, b128=128, b256=256}");

  CLI11_PARSE(app, argc, argv);

  std::shared_ptr<Feature> feature = FeatureFactory::GetFactory(info.c_str());

  //Extract Information
  uint16_t samplesize = 256;
  feature->SetChunkSize(samplesize<<sample);
  std::vector<unsigned int> vent = feature->Extract(filename.c_str());

  //Draw Entropy Image
  auto img = ImageFactory::GetFactory(graphic.c_str());
  img->SetFilename(filename);
  img->SetBlockSize(block);
  img->MakeImage(vent);
  return 0;
}