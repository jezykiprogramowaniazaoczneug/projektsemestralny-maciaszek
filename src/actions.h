#ifndef ACTIONS_H
#define ACTIONS_H

#define ACTIONS_CODE_HELP 0
#define ACTIONS_CODE_ENCRYPT 1
#define ACTIONS_CODE_DECRYPT 2
#define ACTIONS_CODE_ENCODE 3
#define ACTIONS_CODE_DECODE 4

uintmax_t getActionCode(const char* actionText);

#endif
