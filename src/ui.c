#include "globalIncludes.h"
#include "ui.h"

void printHelp(char* executable)
{
  fprintf(stderr, "%s action input [output]\n", executable);

  fprintf(stderr, "\n\n%s\n\n", "action - one of following:");
    fprintf(stderr, "  %s  %s\n", "       help", "display this help");
    fprintf(stderr, "  %s  %s\n", "     --help", "same as 'help'");
    fprintf(stderr, "  %s  %s\n", "    encrypt", "encrypt text with Affine/Caesar cipher");
    fprintf(stderr, "  %s  %s\n", "         en", "same as 'encrypt");
    fprintf(stderr, "  %s  %s\n", "    decrypt", "decrypt text encrypted with Affine/Caesar cipher");
    fprintf(stderr, "  %s  %s\n", "         de", "same as 'decrypt'");

  fprintf(stderr, "\n\n%s\n\n", "input - path to input file or:");
    fprintf(stderr, "  %s  %s\n", "      stdin", "read from stdin");
    fprintf(stderr, "  %s  %s\n", "          -", "same as 'stdin'");
    fprintf(stderr, "  %s  %s\n", "http[s]://…", "read from web resource");

  fprintf(stderr, "\n\n%s\n\n", "output - path to output file or:");
    fprintf(stderr, "  %s  %s\n", "     stdout", "print to stdout (default)");
    fprintf(stderr, "  %s  %s\n", "          -", "same as 'stdout'");

    fprintf(stderr, "\n");
}

void printError(char* errorText)
{
  fprintf(stderr, "\n\033[1;31mERROR: %s\033[0m\n", errorText);
}

void printProgress(uintmax_t done, uintmax_t all)
{
  const uintmax_t greenBlocks = (done*PROGRESS_BAR_WIDTH) / all;
  const uintmax_t percentDone = (done*100) / all;

  if(percentDone < 100)
    fprintf(stderr, " ");
  if(percentDone < 10)
    fprintf(stderr, " ");
  fprintf(stderr, "\033[1;37m%lu%% ", percentDone);

  fprintf(stderr, "\033[0;42m"); //change background to green
  for(uintmax_t i = 0; i < greenBlocks; ++i)
  {
    fprintf(stderr, " ");
  }
  fprintf(stderr, "\033[0;47m"); //change background to white
  for(uintmax_t i = greenBlocks; i < PROGRESS_BAR_WIDTH; ++i)
  {
    fprintf(stderr, " ");
  }
  fprintf(stderr, "\033[0m"); //go back to default colors

  if(percentDone == 100)
    fprintf(stderr, "\n");
  else
    fprintf(stderr, "\r");
}
