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

// Namespace
using namespace std;

// Config stuff
#define CHART_HEIGHT 480
#define BAR_HEIGHT 20

// Main function
int main(int argc, char **argv)
{
  // Some variables
  size_t height = CHART_HEIGHT + BAR_HEIGHT;
  size_t width;
  unsigned char *raw, *all;
  Entropy myent;
  int SampleLength;

  // Show banner
  puts("Ent v.0.1, an entropy level and FPU density measurement tool\n"
       "for ELF                                                     \n"
       "                                             by Lattce Chang\n");

  // Check the arguments
  if (argc < 2)
  {
    // Show usage and quit
    printf("usage: ent <FileName> [<SampleLength>]\n"
           "SampleLength is 256 bytes by default\n");
    return 1;
  }

  // Any non-standard sample length?
  if (argc == 3)
    myent.SetChunkSize(atoi(argv[2]));

  size_t s, i, sz;

  auto img = ImageFactory::GetFactory("png");

  std::vector<unsigned int>vent = myent.Extract(argv[1]);
  
  std::ifstream file(argv[1], std::ios::binary);

  
  return 0;
}