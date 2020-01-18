#include "globalIncludes.h"
#include "actions.h"

uintmax_t getActionCode(const char* actionText)
{
  if(strcmp(actionText, "encrypt") == 0)
    return ACTIONS_CODE_ENCRYPT;
  if(strcmp(actionText, "decrypt") == 0)
    return ACTIONS_CODE_DECRYPT;
  if(strcmp(actionText, "encode") == 0)
    return ACTIONS_CODE_ENCODE;
  if(strcmp(actionText, "decode") == 0)
    return ACTIONS_CODE_DECODE;
  return ACTIONS_CODE_HELP;
}
