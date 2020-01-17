#include "globalIncludes.h"
#include "ui.h"

void printHelp(char* executable)
{
  printf("%s action input [output]\n", executable);

  printf("\n\n%s\n\n", "action - one of following:");
    printf("  %s  %s\n", "       help", "display this help");
    printf("  %s  %s\n", "     --help", "same as 'help'");
    printf("  %s  %s\n", "    encrypt", "encrypt text with Affine/Caesar cipher");
    printf("  %s  %s\n", "         en", "same as 'encrypt");
    printf("  %s  %s\n", "    decrypt", "decrypt text encrypted with Affine/Caesar cipher");
    printf("  %s  %s\n", "         de", "same as 'decrypt'");

  printf("\n\n%s\n\n", "input - path to input file or:");
    printf("  %s  %s\n", "      stdin", "read from stdin");
    printf("  %s  %s\n", "          -", "same as 'stdin'");
    printf("  %s  %s\n", "http[s]://…", "read from web resource");

  printf("\n\n%s\n\n", "output - path to output file or:");
    printf("  %s  %s\n", "     stdout", "print to stdout (default)");
    printf("  %s  %s\n", "          -", "same as 'stdout'");

    printf("\n");
}

void printError(char* errorText)
{
  printf("\n\033[1;31mERROR: %s\033[0m\n", errorText);
}

void printProgress(uintmax_t done, uintmax_t all)
{
  const uintmax_t greenBlocks = (done*PROGRESS_BAR_WIDTH) / all;
  const uintmax_t percentDone = (done*100) / all;

  if(percentDone < 100)
    printf(" ");
  if(percentDone < 10)
    printf(" ");
  printf("\033[1;37m%lu%% ", percentDone);

  printf("\033[0;42m"); //change background to green
  for(uintmax_t i = 0; i < greenBlocks; ++i)
  {
    printf(" ");
  }
  printf("\033[0;47m"); //change background to white
  for(uintmax_t i = greenBlocks; i < PROGRESS_BAR_WIDTH; ++i)
  {
    printf(" ");
  }
  printf("\033[0m"); //go back to default colors

  if(percentDone == 100)
    printf("\n");
  else
    printf("\r");
  fflush(stdout);
}
