#include "globalIncludes.h"
#include "ioOperations.h"

uintmax_t getInputCategory(const char* inputText)
{
  if((strcmp("stdin", inputText) == 0) || (strcmp("-", inputText) == 0))
    return IO_CODE_STDSTREAM;
  if((strstr(inputText, "http://") == inputText) || (strstr(inputText, "https://") == inputText))
    return IO_CODE_URL;
  return IO_CODE_FILE;
}

uintmax_t getOutputCategory(const char* outputText)
{
  if((strcmp("stdout", outputText) == 0) || (strcmp("-", outputText) == 0))
    return IO_CODE_STDSTREAM;
  return IO_CODE_FILE;
}

uintmax_t getFileSize(FILE* file)
{
  uintmax_t size = 0;
  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  rewind(file);
  return size;
}
