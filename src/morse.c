#include "globalIncludes.h"
#include "stringOperations.h"
#include "morse.h"
#include "ui.h"

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
  char* morse = emptyString();
  const uintmax_t latinLength = (uintmax_t)strlen(latin);
  for(uintmax_t i = 0; i < latinLength; ++i)
  {
    if(latin[i] == ' ' || latin[i] == '\n' || latin[i] == '\t'){
      morse = stringAppendString(morse, (char*)morseWordSeparator);
      continue;
    }

    char* toAppend = (char*)latinToMorse(latin[i]);
    if(toAppend == NULL){
      continue;
    }
    morse = stringAppendString(morse, toAppend);
    if(i+1 < latinLength)
      morse = stringAppendString(morse, (char*)morseSymbolSeparator);
  }
  return morse;
}

const char morseToLatin(char* morse)
{
  for(uintmax_t i = 0; i < MORSE_TABLE_SIZE; ++i)
  {
    if(strcmp(morse, morseTable[i][1]) == 0){
      return morseTable[i][0][0];
    }
  }
  return 0;
}

char* morseDecode(char* morse)
{
  char* latin = emptyString();
  const uintmax_t morseLength = (uintmax_t)strlen(morse);
  uintmax_t spaces = 0;
  char* letter = emptyString();
  for(uintmax_t i = 0; i < morseLength; ++i)
  {
    if(spaces == 5){
      latin = stringAppendChar(latin, ' ');
      spaces = 0;
    }

    if(morse[i] == ' '){
      ++spaces;
      if(letter != emptyString()){
        char toAppend = morseToLatin(letter);
        if(toAppend != '\0');
          latin = stringAppendChar(latin, toAppend);
        free(letter);
        letter = emptyString();
      }
    }
    else if(morse[i] == '.' || morse[i] == '-'){
      spaces = 0;
      letter = stringAppendChar(letter, morse[i]);
    }
  }

  if(letter != emptyString()){
    if(strlen(letter) > 0){
      latin = stringAppendChar(latin, morseToLatin(letter));
    }
    free(letter);
  }
  return latin;
}
