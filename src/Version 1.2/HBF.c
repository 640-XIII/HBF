#include <stdio.h>
#include <stdlib.h>

#define INSTRUCTION_LENGTH 4 // LENGTH + 1 ( for \n character)
#define MAXIMUM_LABELS 64
#define MAXIMUM_FUNCS 64
#define MEMORY 256

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
#define RUN_ERR(line) ERROR(RUNTIME_ERROR, ((line + 4) / 4), 3)
#define IS_INT(x) (*x - 48) < 10 && (*x - 48) >= 0
#define FALSE 'f'
#define TRUE 't'

typedef long int LONG;


#pragma region declareFuncs

void loadProgramInMemory(FILE *fp, char *PD, int fileLength);
short interpeter(char *PD, int fileLength);
LONG power(LONG arg1, LONG arg2);
int getFileLength(FILE *fp);

#pragma endregion declareFuncs


int main(int argc, char** argv) {
    if (argc == 1) {
        printf("%s\n", NO_INPUT_FILE); 
        exit(NO_INPUT_FILE_CODE);
    }
    

    FILE *fp = fopen(argv[1], "r");
    int fileLength = getFileLength(fp);
    char *programData = (char *) malloc(fileLength);

    if (fp != NULL) {
        loadProgramInMemory(fp, programData, fileLength);
        
        if (fclose(fp) == 0) {
            return interpeter(programData, fileLength);
        } else {
            printf("%s\n", ERROR_CLOSING_FILE);
            return ERROR_CLOSING_FILE_CODE;
        }
    } else {
        printf("%s\n",ERROR_OPENING_FILE);
        return ERROR_OPENING_FILE_CODE;
    }
}


#pragma region funcs

void loadProgramInMemory(FILE *fp, char *PD, int fileLength) {
    // loads all the data from the file to the PD ( Program Data ) and increases
    // it's value ( address ) by one for the next character

    for (int i = 0; i < fileLength; i++) {
        *(PD + i) = fgetc(fp);
    }
}


short interpeter(char *PD, int fileLength) {
    // all the variables needed to make labels work ( name, label position , number of labels )
    unsigned int *labelsPositions = (int *) malloc(MAXIMUM_LABELS * sizeof(int));
    unsigned char *labelNames = (char *) malloc(MAXIMUM_LABELS);

    unsigned int numOfLabels = 0;


    // all the necessary information about function ( name, line, current function etc )
    unsigned char *functionNames = (char *) malloc(MAXIMUM_FUNCS);
    unsigned char *funcPointer = (char *) malloc(MAXIMUM_FUNCS);

    unsigned int currentFunction = 0;
    unsigned int numOfFunctions = 0;
    unsigned int whereToReturn = 0;
    unsigned int timesCalled = 0;


    // all the data related variables and help variables
    unsigned char *memory = (char *) malloc(MEMORY);
    unsigned int tempVar = 0;
    unsigned int line = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned char found = FALSE;


    // the following loop while end once it sees the E character at PD[0]
    while (*PD != 'E') {
        /* 
        | a switch to effectively test every situation, every time we get into a case
        | we increase the PD ( Program Data ) by one so we have the next character to
        | analyze 
        */
        switch (*PD)
        {
            case ('A'):
                PD++;

                switch (*PD)
                {
                    case ('D'):
                        PD++;

                        // seeing if the character we got is an integer by the #define we created
                        // in the start of the file else inform the user a error is present at i line

                        if (IS_INT(PD)) {
                            *memory += *PD - 48;
                        } else if (*PD == 'P') {
                            *memory += *(memory - 1);
                        } else if (*PD == 'N') {
                            *memory += *(memory + 1);
                        } else {
                            RUN_ERR(line)
                        }


                        PD++;
                        
                        if (*PD != 10) {
                            RUN_ERR(line)
                        }

                        break;
                    
                    default: RUN_ERR(line)
                }

                break;

            case ('D'):
                PD++;
                
                switch (*PD)
                {
                    case ('I'):
                        PD++;

                        // display the character in the selected memory cell
                        if (*PD == 'S') {
                            printf("%c", *memory);
                            PD++;
                        } else { 
                            RUN_ERR(line)
                        }

                        break;

                    case ('E'):
                        PD++;

                        /* 
                        | decrease the value of the cell by one ( value ranges from 0 to 255 )
                        | and there is not protection for overflow - underflow because in some
                        | cases it may help the developer 
                        */

                        if (*PD == 'C') { 
                            *memory -= 1;
                            PD++;
                        } else { 
                            RUN_ERR(line) 
                        }

                        break;

                    case ('V'):
                        PD++;

                        // divide the number ( values range from 0 to 255 ) by the number in
                        // PD[2] if it is a number
                        if (IS_INT(PD)) {
                            *memory = *memory / (*PD - 48);
                            PD++;

                            if (*PD != 10) {
                                RUN_ERR(line)
                            }
                        } else { 
                            RUN_ERR(line) 
                        }
                        
                        break;

                    default: RUN_ERR(line)
                }
                
                break;
            case ('I'):
                PD++;

                switch (*PD)
                {
                    case ('N'):
                        PD++;

                        /* 
                        | increase the value of the selected memory cell by one and like the DEC
                        | command no protection against underflow or overflow because it may
                        | help the developer in some cases 
                        */

                        if (*PD == 'C') {
                            *memory += 1;
                            PD++;
                        } else {
                            RUN_ERR(line)
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;
            
            case ('P'):
                PD++;

                switch (*PD)
                {
                    case ('R'):
                        PD++;

                        // change the memory cell by the selected memory cell - 1 aka the 
                        // previous cell 
                        if (*PD == 'E') {
                            memory--;
                            PD++;
                        } else { 
                            RUN_ERR(line) 
                        }

                        break;

                    case ('W'):
                        PD++;

                        /* 
                        | if the number is a number ( ASCII values 48 - 57 ) then get the number
                        | from the current memory cell and increase it's value to the power of
                        | the number, it does not offer overflow - underflow protection 
                        */

                        if (IS_INT(PD)) {
                            *memory = power(*memory, (*PD - 48));
                            PD++;

                            if (*PD != 10) {
                                RUN_ERR(line)
                            }
                        } else { 
                            RUN_ERR(line) 
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;

            case ('N'):
                PD++;

                switch (*PD) {
                    case ('E'):
                        PD++;

                        // go to the next cell of the memory ( current cell + 1 )
                        if (*PD == 'X') {
                            memory++;
                            PD++;
                        } else { 
                            RUN_ERR(line)
                        }
                        
                        break;

                    case ('W'):
                        PD++;

                        // create a new line character in the terminal 
                        if (*PD == 'L') {
                            printf("\n");
                            PD++;
                        } else {
                            RUN_ERR(line)
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;

            case ('G'):
                PD++;

                switch (*PD)
                {
                    case ('E'):
                        PD++;

                        // gets the character the user gives and stores it into the selected
                        // memory cell ( current memory cell )
                        if (*PD == 'T') {
                            *memory = getchar();
                            getchar();
                            PD++;
                        } else { 
                            RUN_ERR(line) 
                        }

                        break;

                    case ('O'):
                        PD++;

                        // go to the start of list before searching for the labels
                        // and create a found variable for later use
                        found = FALSE;

                        for (j = 0; j < numOfLabels; j++) {
                            labelsPositions--;
                            labelNames--;
                        }
                        /* 
                        | search every label name, if it finds the correct label name
                        | then it will increase the PD ( Program Data ) and return
                        | back to the empty memory cells for future labels, if it
                        | does not find the label increase the positions pointer and
                        | names pointer 
                        */

                        for (j = 0; j < numOfLabels && found == FALSE; j++) {
                            if (*PD == *labelNames) {
                                for (k = 0; k < ((line - *labelsPositions) / 4); k++) {
                                    PD -= INSTRUCTION_LENGTH;
                                } 
                                
                                line = *labelsPositions;

                                for (k = 0; k < numOfLabels - j; k++) {
                                    labelsPositions++;
                                    labelNames++;
                                }

                                found = TRUE;
                                PD++;
                            } else {
                                labelsPositions++;
                                labelNames++;
                            }
                        }

                        // if the label was not found then terminate the program
                        if (found == FALSE) {
                            printf("%s\n", UKNOWN_LABEL_RUNTIME);
                            return UKNOWN_LABEL_RUNTIME_CODE;
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;

            case ('C'):
                PD++;

                switch (*PD) {
                    case ('M'):
                        PD++;

                        /*
                        | CMT and CMF stands for compare true - compare false, if the current
                        | cell of memory in CMT is greater than 0 then executing the following
                        | line of code else ignore it, CMF works the same way but ignores the
                        | following line of code the the value of the cell is not 0
                        */

                        if (*PD == 'T') {
                            if (*memory == 0) {
                                PD += INSTRUCTION_LENGTH;
                                line += INSTRUCTION_LENGTH;
                            } 
                        } else if (*PD == 'F') {
                            if (*memory != 0) {
                                PD += INSTRUCTION_LENGTH;
                                line += INSTRUCTION_LENGTH;
                            }
                        } else {
                            RUN_ERR(line);
                        } 
                        
                        PD++;

                        break;
                    
                    case ('P'):
                        PD++;

                        // copies the value of the current memory cell to the next ( CPN )
                        // or previous ( CPP )
                        if (*PD == 'N') {
                            *(memory + 1) = *memory;
                        } else if (*PD == 'P') {
                            *(memory - 1) = *memory;
                        } else {
                            RUN_ERR(line)
                        }

                        PD++;

                        break;

                    case ('L'):
                        PD++;

                        /*
                        | create a found variable and search every label name, if it finds it
                        | then the found variable become true for later use
                        */

                        found = FALSE;

                        for (j = 0; j < numOfFunctions && found == FALSE; j++) {
                            functionNames--;
                            funcPointer--;

                            if (*PD == *functionNames) {
                                found = TRUE;
                            }
                        }

                        /* 
                        | if the function name was found then decrease the PD (Program Data )
                        | pointer value ( address ) to where the function name was decleare
                        | + 1 lines and reset the function names and pointer addresses back
                        | were they where, if the function was not found then terminate the
                        | program
                        */

                        if (found == TRUE) {
                            for (k = 0; k < ((line - *funcPointer) / 4); k++) {
                                PD -= INSTRUCTION_LENGTH;
                            } 

                            whereToReturn = line;
                            currentFunction = j;
                            line = *funcPointer;

                            for (k = 0; k < j; k++) {
                                functionNames++;
                                funcPointer++;
                            }
                        } else {
                            printf("%s\n", FUNCTION_DOESNT_EXIST);
                            return FUNCTION_DOESNT_EXIST_CODE;
                        }

                        PD++;

                        break;

                    default: RUN_ERR(line)
                }

                break;

            case ('L'):
                PD++;

                switch (*PD) {
                    case ('B'):
                        PD++;

                        /*
                        | creates a found variable and searches every label name, if it finds
                        | the label name the PD[2] has then change the value of found to TRUE
                        | ( 't' ) and terminate the for loop
                        */

                        found = FALSE;

                        for (j = 0; j < (numOfLabels + 1) && found == FALSE; j++) {
                            if (*labelNames == *PD) {
                                found = TRUE;
                            } else {
                                *labelNames--;
                            }
                        }


                        /*
                        | if the label was not find create the label and store it's name and
                        | position to the label position - name pointer and increase their 
                        | values ( addresses ) by one and also increase the num of labels by
                        | one, if it is found then terminate the program
                        */

                        if (found == FALSE) {
                            for (k = 0; k < j; k++) { labelNames++; }

                            *labelsPositions = line;
                            *labelNames = *PD;

                            labelsPositions++;
                            labelNames++;

                            numOfLabels++;
                            PD++;
                        } else {
                            printf("%s\n", LABEL_ALREADY_EXISTS);
                            return LABEL_ALREADY_EXISTS_CODE;
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;
            
            case ('R'):
                PD++;

                switch (*PD) {
                    case ('R'):
                        PD++;

                        // if the character is a number ( ASCII 48 - 57 ) then store to the current
                        // memory cell the remainder of *value % *PD
                        if (IS_INT(PD)) {
                            *memory = *memory % (*PD - 48);
                        } else {
                            RUN_ERR(line)
                        }

                        PD++;

                        // if the current PD ( Program Data character ) is not equal to 10 ( \n )
                        // then throw a runtime error to the line it was encountered ( (i / 4) + 1 )  
                        if (*PD != 10) {
                            RUN_ERR(line)
                        } 

                        break;
                    
                    case ('E'):
                        PD++;

                        if (*PD == 'T') {

                            // this is used to return to the CL* from the end of the called function
                            tempVar = line;
                            PD++;

                            for (j = 0; j < (whereToReturn - tempVar) / 4; j++) {
                                PD += INSTRUCTION_LENGTH;
                                line += INSTRUCTION_LENGTH;
                            }
                        } else {
                            RUN_ERR(line)
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;
            
            case ('S'):
                PD++;

                switch (*PD) {
                    case ('U'):
                        PD++;

                        /* 
                        | if the PD[2] is a number ( ASCII values 48 - 57 ) then substract
                        | the current memory cell value with the PD[2] character value - 48
                        | this does not protect against overflow - underflow 
                        */

                        if (IS_INT(PD)) {
                            *memory = *memory - (*PD - 48);
                            PD++;

                            if (*PD != 10) {
                                RUN_ERR(line)
                            }
                        } else {
                            RUN_ERR(line)
                        }

                        break;

                    case ('S'):
                        PD++;

                        if (IS_INT(PD)) {
                            for (j = 0; j < *(PD) - 48; j++) {
                                printf("%c", *(memory + j));
                            }

                            PD++;
                        } else {
                            RUN_ERR(line);
                        }

                        break;

                    default: RUN_ERR(line)
                }

                break;

            case ('M'):
                PD++;

                switch (*PD)
                {
                    case ('V'):
                        PD++;

                        // store the PD[2] value to the current memory cell
                        *memory = *PD;
                        PD++;

                        break;

                    default: RUN_ERR(line)
                }

                break;
            
            case ('F'):
                PD++;

                switch (*PD) {
                    case ('N'):
                        PD++;

                        // searches if a function with the PD[2] name already exists,
                        // if it exists the changes the found value to TRUE
                        short toIncrease = 0;
                        found = FALSE;

                        for (j = 0; j < numOfFunctions && found == FALSE; j++) {
                            functionNames--;

                            if (*functionNames == *PD) {
                                found = TRUE;
                            }
                        }


                        /*
                        | if it did not find a function with the name PD[2] then reset
                        | the function names value ( addresses ) back to where it was,
                        | insert the new values even to function pointer and increase
                        | the addresses by one and PD ( Program Data ) by 2
                        */

                        if (found == FALSE) {
                            for (k = 0; k < j; k++) { functionNames++; }

                            *functionNames = *PD;
                            *funcPointer = line;

                            functionNames++;
                            funcPointer++;

                            numOfFunctions++;
                            PD += 2;


                            /*
                            | search for a RET command and increase the PD ( Program Data )
                            | by how many characters it looked for, if it does find one then
                            | change the value of found to TRUE, if it does not find one and
                            | instead finds the E command at PD[0] it will exit without any
                            | warning to the user
                            */

                            while (found == FALSE) {
                                toIncrease = 0;

                                if (*PD == 'R') {
                                    PD++;

                                    if (*PD == 'E') {
                                        PD++;

                                        if (*PD == 'T') {
                                            found = TRUE;
                                            PD++;
                                        } else {
                                            toIncrease = INSTRUCTION_LENGTH - 2;
                                        }
                                    } else {
                                        toIncrease = INSTRUCTION_LENGTH - 1;
                                    }
                                } else if (*PD == 'E') {
                                    return 0;
                                } else {
                                    toIncrease = INSTRUCTION_LENGTH;
                                }

                                line += INSTRUCTION_LENGTH;
                                PD += toIncrease;
                            }
                        } else {
                            printf("%s\n", FUNCTION_ALREADY_EXISTS);
                            return FUNCTION_ALREADY_EXISTS_CODE;
                        }

                        break;
                    
                    default: RUN_ERR(line)
                }

                break;
        }

        // if the PD[3] does not equal to 10 or the new line character then inform the
        // user at line ( (i + 4) / 4) that the command is larger than allowed 
        if (*PD != 10) {
            printf("PD -> |%c|\n", *PD);
            printf("%s\nLine: %i\n", LARGE_COMMAND, (line + 4) / 4);
            
            return LARGE_COMMAND_CODE;
        }

        // update the line variable by the instruction length and increase PD ( Program Data )
        // by one
        line += INSTRUCTION_LENGTH;
        PD++;
    }

    return 0;
}


LONG power(LONG arg1, LONG arg2) {
    // if the user inputs 0 ( arg1 ^ 0 ) then return 1, if the user inputs 1 ( arg1 ^ 1 )
    // then return arg1

    if (arg2 == 0) {
        return 1;
    } else if (arg2 == 1) {
        return arg1;
    }


    // declare a long variable ( 8 bytes for linux - 4 for windows and i won't change it )
    // to return for later after we finish multiplying the arg1 to itself by arg2 - 1 times
    LONG toReturn = arg1;

    for (short i = 0; i < arg2 - 1; i++) {
        toReturn = toReturn * toReturn;
    }

    return toReturn;
}


int getFileLength(FILE *fp) {
    int toReturn;

    // goes to the end of the file, get's it's length and goes back at the start of the
    // file then returns the length of the file for later use
    fseek(fp, 0, SEEK_END);
    toReturn = ftell(fp);
    rewind(fp);

    return toReturn;
}

#pragma endregion funcs