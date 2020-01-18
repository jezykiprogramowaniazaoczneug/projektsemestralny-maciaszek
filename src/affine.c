#include "globalIncludes.h"
#include "stringOperations.h"
#include "affine.h"
#include "mathOperations.h"

char plainToAffine(char plain, intmax_t a, intmax_t b)
{
  if(plain >= 'a' && plain <= 'z'){
    plain -= 32;
  }
  else if(plain < 'A' || plain > 'Z'){
    return '\0';
  }

  intmax_t affine = plain - 'A';
  affine *= a;
  affine += b;
  affine %= AFFINE_ALPHABET_SIZE;
  if(affine < 0)
    affine += AFFINE_ALPHABET_SIZE;
  affine += 'A';
  return (char)affine;
}

char affineToPlain(char affine, intmax_t a, intmax_t b)
{
  if(affine >= 'a' && affine <= 'z'){
    affine -= 32;
  }
  else if(affine < 'A' || affine > 'Z'){
    return '\0';
  }

  intmax_t plain = affine - 'A';
  plain -= b;
  plain *= multiplicativeInverse(a, AFFINE_ALPHABET_SIZE);
  plain %= AFFINE_ALPHABET_SIZE;
  if(plain < 0)
    plain += AFFINE_ALPHABET_SIZE;
  plain += 'A';
  return (char)plain;
}


char* affineEncrypt(char* plain, intmax_t a, intmax_t b)
{
  char* encrypted = emptyString();
  uintmax_t plainLength = strlen(plain);
  for(uintmax_t i = 0; i < plainLength; ++i)
  {
    char encryptedChar = plainToAffine(plain[i], a, b);
    if(encryptedChar == '\0')
      encrypted = stringAppendChar(encrypted, plain[i]);
    else
      encrypted = stringAppendChar(encrypted, encryptedChar);
  }
  return encrypted;
}

char* affineDecrypt(char* encrypted, intmax_t a, intmax_t b)
{
  char* plain = emptyString();
  uintmax_t encryptedLength = strlen(encrypted);
  for(uintmax_t i = 0; i < encryptedLength; ++i)
  {
    char plainChar = affineToPlain(encrypted[i], a, b);
    if(plainChar == '\0')
      plain = stringAppendChar(plain, encrypted[i]);
    else
      plain = stringAppendChar(plain, plainChar);
  }
  return plain;
}
