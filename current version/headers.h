#ifndef HEADER_DEFINED

#define HEADER_DEFINED

#define INSTRUCTION_LENGTH 4 // LENGTH + 1 ( for \n character)
#define MAXIMUM_LABELS 64
#define MAXIMUM_FUNCS 64
#define MEMORY 256


#define ERROR_CLOSING_FILE "Error closing input file"
#define WRONG_ARGUMENT "Invalid argument, please enter a valid argument"

#define ERROR(line, exitCode) return printf("%s\nLine -> %i\n", errorMessages[exitCode - 1], line), exitCode;
#define RUN_ERR(line) ERROR(((line + INSTRUCTION_LENGTH) / INSTRUCTION_LENGTH), 3)
#define IS_INT(x) (*x - '0') < 10 && (*x - '0') >= 0

#define DEBUG_FILE_OUTPUT_NAME "debugOut.txt"
#define DEBUG_MODE_CODE "-d"

#define FALSE 'f'
#define TRUE 't'

enum ERROR_CODES {
    NO_INPUT_FILE_CODE = 1,
    ERROR_OPENING_FILE_CODE = 2,
    RUNTIME_ERROR_CODE = 3,
    UKNOWN_LABEL_RUNTIME_CODE = 4,
    LABEL_ALREADY_EXISTS_CODE = 5,
    FUNCTION_ALREADY_EXISTS_CODE = 6,
    FUNCTION_DOESNT_EXIST_CODE = 7,
    LARGE_COMMAND_CODE = 8,
    ERROR_CLOSING_FILE_CODE = 9,
    WRONG_ARGUMENT_CODE = 10,
    NO_DEBUG_FILE_CODE = 11
};

const char* errorMessages[] = {
    "No input file detected, please insert the file name",
    "An error occured while opening the file",
    "Error during runtime, unexpected character",
    "Error during runtime, unknown label",
    "Error during runtime, label already exists",
    "Error during runtime, function already exist",
    "Error during runtime, function doesn't exist",
    "Error during runtime, command larger than expected",
    "Error closing input file",
    "Invalid argument, please enter a valid argument"
    "Missing argument, debug output file name"
};

#endif