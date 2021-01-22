#ifndef HEADER_DEFINED

#define HEADER_DEFINED

#define INSTRUCTION_LENGTH 4 // LENGTH + 1 ( for \n character)
#define MAXIMUM_LABELS 64
#define MAXIMUM_FUNCS 64
#define MEMORY 256

#define NO_INPUT_FILE "No input file detected, please insert the file name"
#define ERROR_OPENING_FILE "An error occured while opening the file"
#define RUNTIME_ERROR "Error during runtime, unexpected character"
#define UKNOWN_LABEL_RUNTIME "Error during runtime, unknown label"
#define LABEL_ALREADY_EXISTS "Error during runtime, label already exists"
#define FUNCTION_ALREADY_EXISTS "Error during runtime, function already exist"
#define FUNCTION_DOESNT_EXIST "Error during runtime, function doesn't exist"
#define LARGE_COMMAND "Error during runtime, command larger than expected"
#define ERROR_CLOSING_FILE "Error closing input file"

#define ERROR(message, line, exitCode) printf("%s\nLine -> %i\n", message, line); return exitCode;
#define RUN_ERR(line) ERROR(RUNTIME_ERROR, ((line + INSTRUCTION_LENGTH) / INSTRUCTION_LENGTH), 3)
#define IS_INT(x) (*x - 48) < 10 && (*x - 48) >= 0
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
    ERROR_CLOSING_FILE_CODE = 9
};

typedef long int LONG;

#endif