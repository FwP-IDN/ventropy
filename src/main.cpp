// Includes
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "entropy.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <elf.h>
#endif

#include "imgfactory.h"

using namespace std;

#define CHART_HEIGHT 480
#define BAR_HEIGHT 20

int main(int argc, char **argv)
{
  Entropy myent;

  puts("Ent v.0.1, an entropy level and FPU density measurement tool\n"
       "for ELF                                                     \n"
       "                                             by Lattce Chang\n");
  
  if (argc < 2)
  {
    printf("usage: ent <FileName> [<SampleLength>]\n"
           "SampleLength is 256 bytes by default\n");
    return 1;
  }

  if (argc == 3)
    myent.SetChunkSize(atoi(argv[2]));

  auto img = ImageFactory::GetFactory("png");

  std::string filename(argv[1]);
  size_t extension = filename.find_last_of(".");
  size_t last = filename.find_last_of("/");
  std::string imgname = filename.substr(last+1, extension); 
  std::vector<unsigned int>vent = myent.Extract(argv[1]);
  img->SetFilename(imgname);
  img->MakeImage(vent);
  return 0;
}