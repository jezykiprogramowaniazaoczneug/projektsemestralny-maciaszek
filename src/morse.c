#include "globalIncludes.h"
#include "stringOperations.h"
#include "morse.h"

const char* morseWordSeparator = "     ";
const char* morseSymbolSeparator = " ";
const char* morseTable[MORSE_TABLE_SIZE][2] = {
  {"Aa", ".-"},
  {"Bb","-..."},
  {"Cc","-.-."},
  {"Dd","-.."},
  {"Ee","."},
  {"Ff","..-."},
  {"Gg","--."},
  {"Hh","...."},
  {"Ii",".."},
  {"Jj",".---"},
  {"Kk","-.-"},
  {"Ll",".-.."},
  {"Mm","--"},
  {"Nn","-."},
  {"Oo","---"},
  {"Pp",".--."},
  {"Qq","--.-"},
  {"Rr",".-."},
  {"Ss","..."},
  {"Tt","-"},
  {"Uu","..-"},
  {"Vv","...-"},
  {"Ww",".--"},
  {"Xx","-..-"},
  {"Yy","-.--"},
  {"Zz","--.."},
  {"1",".----"},
  {"2","..---"},
  {"3","...--"},
  {"4","....-"},
  {"5","....."},
  {"6","-...."},
  {"7","--..."},
  {"8","---.."},
  {"9","----."},
  {"0","-----"},
  {",","..-.."},
  {".",".-.-.-"},
  {"?","..--.."},
  {";","-.-.-"},
  {":","---..."},
  {"/","-..-."},
  {"+",".-.-."},
  {"-","-....-"},
  {"=","-...-"}
};

const char* latinToMorse(char latin)
{
  for(uintmax_t i = 0; i < MORSE_TABLE_SIZE; ++i)
  {
    for(uintmax_t j = 0; j < strlen(morseTable[i][0]); ++j)
    {
      if(latin == morseTable[i][0][j])
        return morseTable[i][1];
    }
  }
  return NULL;
}

char* morseEncode(char* latin)
{
  char* morse = malloc(0);
  const uintmax_t latinLength = (uintmax_t)strlen(latin);
  for(uintmax_t i = 0; i < latinLength; ++i)
  {
    if(latin[i] == ' '){
      morse = stringAppend(morse, (char*)morseWordSeparator);
      continue;
    }

    const char* toAppend = latinToMorse(latin[i]);
    if(toAppend == NULL)
      printf("Letter not found");
    morse = stringAppend(morse, toAppend);
    if(i+1 < latinLength)
      morse = stringAppend(morse, (char*)morseSymbolSeparator);
  }
  return morse;
}
