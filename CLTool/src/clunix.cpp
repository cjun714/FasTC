#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TexComp.h"

void PrintUsage() {
   fprintf(stderr, "Usage: tc [-s|-t <num>] <imagefile>\n");
}

int main(int argc, char **argv) {

  int fileArg = 1;
  if(fileArg == argc) {
    PrintUsage();
    exit(1);
  }

  int quality = 50;
  int numThreads = 1;
  bool bUseSIMD = false;
  
  bool knowArg = false;
  do {
    knowArg = false;
    
    if(strcmp(argv[fileArg], "-s") == 0) {
      fileArg++;
      bUseSIMD = true;
      knowArg = true;
    }

    if(strcmp(argv[fileArg], "-t") == 0) {
      fileArg++;
      
      if(fileArg == argc || (numThreads = atoi(argv[fileArg])) < 1) {
	PrintUsage();
	exit(1);
      }

      fileArg++;
      knowArg = true;
    }

    if(strcmp(argv[fileArg], "-q") == 0) {
      fileArg++;
      
      if(fileArg == argc || (quality = atoi(argv[fileArg])) < 0) {
	PrintUsage();
	exit(1);
      }

      fileArg++;
      knowArg = true;
    }

  } while(knowArg);

  if(fileArg == argc) {
    PrintUsage();
    exit(1);
  }

  ImageFile file (argv[fileArg]);
  
  SCompressionSettings settings;
  settings.bUseSIMD = bUseSIMD;
  settings.iNumThreads = numThreads;
  settings.iQuality = quality;

  CompressedImage *ci = CompressImage(file, settings);

  // Cleanup 
  if(NULL != ci)
    delete ci;
  return 0;
}
