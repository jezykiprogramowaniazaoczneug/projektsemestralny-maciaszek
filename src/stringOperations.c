#include "globalIncludes.h"
#include "stringOperations.h"

char* emptyString()
{
  return NULL;
}

char* stringAppendString(char* mainString, char* additionalString)
{
  uintmax_t mainLength = 0;
  if(mainString != NULL)
    mainLength = strlen(mainString);
  char* newString = (char*)malloc(sizeof(char) * (mainLength+strlen(additionalString)+1));
  newString[0] = '\0';
  if(mainString != NULL){
    strcat(newString, mainString);
    free(mainString);
  }
  strcat(newString, additionalString);
  return newString;
}

char* stringAppendChar(char* mainString, const char additionalCharacter)
{
  char* additionalString = (char*)malloc(sizeof(char)*2);
  additionalString[0] = (char)additionalCharacter;
  additionalString[1] = '\0';
  char* newString = stringAppendString(mainString, additionalString);
  free(additionalString);
  return newString;
}
