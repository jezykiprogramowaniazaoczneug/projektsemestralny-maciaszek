#ifndef UI_H
#define UI_H

#define PROGRESS_BAR_WIDTH 74

void printHelp();
void printError(char* errorText);
void printProgress(uintmax_t done, uintmax_t all);

#endif
