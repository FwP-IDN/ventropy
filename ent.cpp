// Includes
#include <cstdio>
#include <cstring>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#endif

#include "imgfactory.h"

// Namespace
using namespace std;

// Config stuff
#define CHART_HEIGHT 480
#define BAR_HEIGHT 20

static double GetEntropy(const unsigned char *Data, int Size);
static unsigned char * FileGetContent(const char *FileName, size_t *Size);


// Main function
int main(int argc, char **argv)
{
  // Some variables
  int SampleLength = 256;
  size_t height = CHART_HEIGHT + BAR_HEIGHT;
  size_t width;
  unsigned char *raw, *all;

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
    SampleLength = atoi(argv[2]);

  // Load the file into memory
  unsigned char *data;
  size_t s, i, sz;

  auto img = ImageFactory::GetFactory("png");
  data = FileGetContent(argv[1], &s);
  if (data == NULL)
  {
    fprintf(stderr, "file not found\n");
    return 2;
  }

  // Allocate space for the chart bitmap
  sz = s - SampleLength;
  width = s / SampleLength;

  all = new unsigned char[width * height * 3];
  raw = all;

  // Paint it white
  memset(raw, 0xff, width * height * 3);

  // Some variables
  size_t j, cnt = 0;

  printf("Calculating entropy...");

  // Calculate and draw the main entropy
  for (i = 0; i < sz; i += SampleLength, cnt++)
  {
    // Some variables
    size_t hi;

    // Calculate the entropy
    double ent = GetEntropy(&data[i], SampleLength);
    ent /= SampleLength;
    ent = 1.0 - ent;
    ent *= ent; // Square scale
    ent *= 100.0;
    hi = CHART_HEIGHT - (int)(ent * ((float)(CHART_HEIGHT - 1) / 100.0f));

    printf("Entropy [(%.8Xh - %.8Xh) = %3i%%]\n", i, i + SampleLength - 1, (int)ent);

    // Precalculate some parts of the color
    int ent_by_100 = (int)(ent * (255.0 / 100.0));
    int ent_by_120 = (int)(ent * (255.0 / 120.0));
    int ent_by_200 = (int)(ent * (255.0 / 200.0));

    // Draw the chart
    for (j = CHART_HEIGHT + BAR_HEIGHT - 1; j >= hi + BAR_HEIGHT; j--)
    {
      if (j - BAR_HEIGHT <= 13)
      {
        // Very high entropy
        raw[(cnt + j * width) * 3 + 2] = 0x00;
        raw[(cnt + j * width) * 3 + 1] = 0x00;
        raw[(cnt + j * width) * 3 + 0] = ent_by_100;
      }
      else if (j - BAR_HEIGHT <= 92)
      {
        // High entropy
        raw[(cnt + j * width) * 3 + 2] = 0x00;
        raw[(cnt + j * width) * 3 + 1] = ent_by_120;
        raw[(cnt + j * width) * 3 + 0] = ent_by_120;
      }
      else if (j - BAR_HEIGHT <= 192)
      {
        // Average entropy
        raw[(cnt + j * width) * 3 + 2] = 0x00;
        raw[(cnt + j * width) * 3 + 1] = ent_by_100;
        raw[(cnt + j * width) * 3 + 0] = 0x00;
      }
      else
      {
        // Low entropy
        raw[(cnt + j * width) * 3 + 2] = ent_by_200;
        raw[(cnt + j * width) * 3 + 1] = 0x00;
        raw[(cnt + j * width) * 3 + 0] = ent_by_200;
      }
    } // for
  }   // for

  // Skip to next line
  putchar('\n');

  // Delete the file data
  free(data);

  
  // Free the memory
  delete all;

  // It's done.
  puts("Done.");

  // Done
  return 0;
}

//
// FileGetContent
//
static unsigned char *
FileGetContent(const char *FileName, size_t *Size)
{
  // Some variables
  FILE *f;
  size_t FileSize;
  unsigned char *Data;

  // Open the file
  f = fopen(FileName, "rb");
  if (!f)
    return NULL;

  // Get file size
  fseek(f, 0, SEEK_END);
  FileSize = ftell(f);
  fseek(f, 0, SEEK_SET);

  // Allocate memory
  Data = (unsigned char *)malloc(FileSize + 1);
  if (!Data)
  {
    fclose(f);
    return NULL;
  }

  // Read file content
  FileSize = fread(Data, 1, FileSize, f);
  Data[FileSize] = 0;

  // Close the file
  fclose(f);

  // Return
  if (Size) // Size is optional
    *Size = FileSize;
  printf("size %d\n", Size);
  return Data;
}

//
// MakeHistogram Function
//
static void
MakeHistogram(const unsigned char *Data, int Size, int Array[256])
{
  // Some variable
  int i;

  // Zero it!
  memset(Array, 0, sizeof(int) * 256);

  // Fill the array
  for (i = 0; i < Size; i++)
    Array[Data[i]]++;
}

//
// GetEntropy Function
//
static double
GetEntropy(const unsigned char *Data, int Size)
{
  // Some variables
  int Array[256];
  int i;
  double Entropy = 0.0;

  // Create the histogram
  MakeHistogram(Data, Size, Array);

  // Calculate the entropy
  for (i = 0; i < 256; i++)
  {
    double Pr = (double)Array[i] / Size;
    Entropy += Pr * (double)Array[i];
  }

  // Return the entropy
  return Entropy;
}