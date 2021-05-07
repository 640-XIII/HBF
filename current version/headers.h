#ifndef IFNDEFDEFINED
#define IFNDEFDEFINED

struct ProgramData
{
    char opcode[3];
};


typedef enum {
    FALSE, TRUE
} boolean;


int getTotalLines(FILE *fp);
void readFileData(FILE *fp, struct ProgramData toWrite[], int totalLines);
int interpreter(struct ProgramData toAnalyze[], int totalLines);
int power(int base, int exponent);


#define isNumber(character) (character - '0') >= 0 && (character - '0') <= 9 

#define printError(errorMessage, returnCode) return printf("Error: %s\n", errorMessage), returnCode;
#define printErrorLine(errorMessage, line, returnCode) return printf("Error: %s\nLine: %i\n", errorMessage, (line + 1)), returnCode;
#define wrongOpcode printErrorLine(INCORRECT_OPCODE_ERROR_MESSAGE, line, INCORRECT_OPCODE_ERROR_CODE)

#define OPCODE_SIZE 3

#define NO_INPUT_FILE_ERROR_CODE 1
#define INCORRECT_OPCODE_ERROR_CODE 2
#define WRONG_ARGUMENT_ERROR_CODE 3
#define WRONG_VALUE_ERROR_CODE 4
#define ARITHMETIC_ERROR_CODE 5
#define LABEL_ALREADY_EXISTS_ERROR_CODE 6

#define NO_INPUT_FILE_ERROR_MESSAGE "No input file detected"
#define INCORRECT_OPCODE_ERROR_MESSAGE "Incorrect opcode"
#define WRONG_ARGUMENT_ERROR_MESSAGE "Wrong argument given"
#define WRONG_VALUE_ERROR_MESSAGE "Wrong value given"
#define ARITHMETIC_ERROR_MESSAGE "Arithmetic error"
#define LABEL_ALREADY_EXISTS_ERROR_MESSAGE "Label already exists"

#endif
