#include "globalIncludes.h"
#include "stringOperations.h"
#include "morse.h"
#include "mathOperations.h"
#include "affine.h"
#include "ui.h"
#include "ioOperations.h"
#include "actions.h"

#define ACTION argv[1]
#define INPUT argv[2]
#define OUTPUT argv[3]

#define BUFFER_SIZE 8192

int main(int argc, char** argv)
{
  if(argc < 2){
    printError("Too few arguments");
    printHelp(argv[0]);
    return 0;
  }

  const uintmax_t actionCode = getActionCode(ACTION);

  if(actionCode == ACTIONS_CODE_HELP){
    printHelp(argv[0]);
    return 0;
  }

  if(argc < 4){
    printError("Too few arguments");
    printHelp(argv[0]);
    return 0;
  }

  printf("Initializing... ");
  fflush(stdout);

  const uintmax_t inputCategory = getInputCategory(INPUT);
  const uintmax_t outputCategory = getOutputCategory(OUTPUT);
  FILE* input;
  FILE* output;
  uintmax_t inputLength = 0;
  uintmax_t dataRead = 0;
  uintmax_t lastDataRead = 0;
  char* inputBuffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
  intmax_t keyA = 1;
  intmax_t keyB = 3;
  char* inputSupportBuffer = emptyString();

  if(outputCategory == IO_CODE_FILE){
    output = fopen(OUTPUT, "w");
    if(output == NULL){
      printError("Failed creating output file");
      return 0;
    }
  }
  else if(outputCategory == IO_CODE_STDSTREAM){
    output = stdout;
  }

  if(inputCategory == IO_CODE_FILE){
    input = fopen(INPUT, "r");
    if(input == NULL){
      printError("Failed opening input file");
      return 0;
    }
    inputLength = getFileSize(input);
  }
  else if(inputCategory == IO_CODE_URL){
    if(system("mkdir /tmp/projektsemestralny-maciaszek/") != 0){
      printError("Failed creating directory /tmp/projektsemestralny-maciaszek/");
      return 0;
    }
    char* command = emptyString();
    command = stringAppendString(command, "curl -s -o /tmp/projektsemestralny-maciaszek/webContent.txt ");
    command = stringAppendString(command, INPUT);
    if(system(command) != 0){
      printError("Failed downloading web content");
      return 0;
    }
    free(command);

    input = fopen("/tmp/projektsemestralny-maciaszek/webContent.txt", "r");
    if(input == NULL){
      printError("Failed opening input file");
      return 0;
    }
    inputLength = getFileSize(input);
  }
  else if(inputCategory == IO_CODE_STDSTREAM){
    input = stdin;
  }

  printf("OK\n");

  if(actionCode == ACTIONS_CODE_ENCRYPT || actionCode == ACTIONS_CODE_DECRYPT){
    fprintf(stderr, "Please provide keyA (1 for Caesar cipher): ");
    scanf("%lu", &keyA);
    fprintf(stderr, "Please provide keyB (3 for Caesar cipher): ");
    scanf("%lu", &keyB);

    if(multiplicativeInverse(keyA, AFFINE_ALPHABET_SIZE) == 0){
      printError("Invalid keyA");
      return 0;
    }
  }

  if(inputCategory != IO_CODE_STDSTREAM){
    printProgress(0, inputLength);
  }
  while(fgets(inputBuffer, BUFFER_SIZE, input) != NULL)
  {
    char* outputBuffer = emptyString();
    if(actionCode == ACTIONS_CODE_DECODE){
      char* tmpString;
      if(inputSupportBuffer != emptyString()){
        tmpString = (char*)malloc(sizeof(char)*strlen(inputSupportBuffer));
        strcpy(tmpString, inputSupportBuffer);
        tmpString = stringAppendString(tmpString, inputBuffer);
        free(inputSupportBuffer);
        inputSupportBuffer = generateSupportBuffer(tmpString);
        outputBuffer = morseDecode(tmpString);
        free(tmpString);
      }
      else{
        inputSupportBuffer = generateSupportBuffer(inputBuffer);
        outputBuffer = morseDecode(inputBuffer);
      }
    }
    else if(actionCode == ACTIONS_CODE_ENCODE){
      outputBuffer = morseEncode(inputBuffer);
    }
    else if(actionCode == ACTIONS_CODE_ENCRYPT){
      outputBuffer = affineEncrypt(inputBuffer, keyA, keyB);
    }
    else if(actionCode == ACTIONS_CODE_DECRYPT){
      outputBuffer = affineDecrypt(inputBuffer, keyA, keyB);
    }
    else{
      printError("Unknown action");
      return 0;
    }
    if(outputBuffer == NULL){
      printError("Processing failed");
      return 0;
    }

    fprintf(output, "%s", outputBuffer);
    free(outputBuffer);

    if(inputCategory != IO_CODE_STDSTREAM){
      dataRead = ftell(input);
      if(((dataRead - lastDataRead)*100/inputLength > 0) || ((dataRead - lastDataRead)*PROGRESS_BAR_WIDTH/inputLength > 1)){
        printProgress(dataRead, inputLength);
        lastDataRead = dataRead;
      }
    }
  }
  if(inputSupportBuffer != emptyString() && actionCode == ACTIONS_CODE_DECODE){
      char* outputBuffer = morseDecode(inputSupportBuffer);
      if(outputBuffer == NULL){
        printError("Processing failed");
        return 0;
      }
      fprintf(output, "%s", outputBuffer);
      free(outputBuffer);
  }

  if(inputCategory != IO_CODE_STDSTREAM){
    dataRead = ftell(input);
    if(((dataRead - lastDataRead)*100/inputLength > 0) || ((dataRead - lastDataRead)*PROGRESS_BAR_WIDTH/inputLength > 1)){
      printProgress(dataRead, inputLength);
      lastDataRead = dataRead;
    }
  }

  if(inputCategory != IO_CODE_STDSTREAM)
    fclose(input);
  if(outputCategory != IO_CODE_STDSTREAM)
    fclose(output);
  if(inputCategory == IO_CODE_URL){
    if(system("rm -rf /tmp/projektsemestralny-maciaszek/") != 0){
      printError("Failed removing temporary files");
    }
  }

  free(inputBuffer);

  return 0;
}
