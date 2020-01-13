#include "globalIncludes.h"
#include "stringOperations.h"

char* stringAppend(char* mainString, const char* additionalString)
{
  mainString = realloc(mainString, sizeof(char)*(strlen(mainString) + strlen(additionalString)));
  strcat(mainString, additionalString);
  return mainString;
}
