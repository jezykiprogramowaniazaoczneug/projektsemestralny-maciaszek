#ifndef MORSE_H
#define MORSE_H

#define MORSE_TABLE_SIZE 45

const char* morseWordSeparator;
const char* morseSymbolSeparator;
const char* morseTable[MORSE_TABLE_SIZE][2];
const char* latinToMorse(char latin);
char* morseEncode(char* latin);
const char morseToLatin(char* morse);
char* morseDecode(char* morse);

#endif
