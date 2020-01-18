#ifndef IO_OPERATIONS_H
#define IO_OPERATIONS_H

#define IO_CODE_FILE 0
#define IO_CODE_STDSTREAM 1
#define IO_CODE_URL 2

uintmax_t getInputCategory(const char* inputText);
uintmax_t getOutputCategory(const char* outputText);
uintmax_t getFileSize(FILE* file);

#endif
