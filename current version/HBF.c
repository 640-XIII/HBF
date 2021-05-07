#include <stdio.h>
#include <stdlib.h>
#include "header.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        printError(NO_INPUT_FILE_ERROR_MESSAGE, NO_INPUT_FILE_ERROR_CODE);
    }

    FILE *fp = fopen(argv[1], "r");
    int totalLines = getTotalLines(fp);
    struct ProgramData PD[totalLines];
    
    readFileData(fp, PD, totalLines);
    fclose(fp);

    return interpreter(PD, totalLines);
}


#pragma region funcs

int getTotalLines(FILE *fp) {
    int toReturn = 1;
    char toAnalyze;

    do {
        toAnalyze = fgetc(fp);

        if (toAnalyze == '\n') {
            toReturn++;
        }
    } while (toAnalyze != EOF);

    rewind(fp);

    return toReturn;
}


void readFileData(FILE *fp, struct ProgramData toWrite[], int totalLines) {
    char characterToAnalyze;
    
    for (unsigned int i = 0; i < totalLines; i++) {
        for (int j = 0; j < 3; j++) {
            toWrite[i].opcode[j] = fgetc(fp);
        }

        do {
            characterToAnalyze = fgetc(fp);
        } while (characterToAnalyze != 10 && characterToAnalyze != EOF);
    }
}


int power(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent == 1) {
        return base;
    }


    int reserve = base;
    
    for (int i = 1; i < exponent; i++) {
        base *= reserve;
    }

    return base;
}


int interpreter(struct ProgramData toAnalyze[], int totalLines) {
    // main memory ( 0 - 255 range )
    unsigned char *mainMemory = malloc(3);
    unsigned int mainMemorySize = 3;
    unsigned int currentByte = 1;

    // extended memory ( 0 - 65535 range )
    unsigned short *extendedMemory = malloc(3 * sizeof(short));
    unsigned int extendedMemorySize = 3;
    unsigned int extendedCurrentByte = 1;

    // label pointers (name, line) and a variable to keep track of the total labels
    unsigned char *labelName = malloc(1);
    unsigned int *labelLine = malloc(1 * sizeof(int));
    unsigned int totalLabels = 0;
    boolean foundLabel = FALSE;

    // function pointers (name, line) and a variable to keep track of the total functions declared, functions look a lot
    // like labels
    unsigned char *functionName = malloc(1);
    unsigned int *functionLine = malloc(1 * sizeof(int));
    unsigned int totalFunctions = 0;
    unsigned int lineCalled = 0;
    boolean foundFunction = FALSE;

    // initializing values to all three starter cells, this is done to avoid further confusion with logical errors in
    // the code (ADP, ADN, AP*, AN*), this is the easiest and best solution
    *mainMemory = 0;
    *(mainMemory + 1) = 0;
    *(mainMemory + 2) = 0;

    // initializing values to all three EM cells to avoid further confusion
    *extendedMemory = 0;
    *(extendedMemory + 1) = 0;
    *(extendedMemory + 2) = 0;


    for (unsigned int line = 0; line < totalLines; line++) {
        switch (toAnalyze[line].opcode[0])
        {
            case 'A':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'D':
                        // a lazy solution to prevent the user from running arithmetic operations dependent on the 
                        // main memory cells
                        if (mainMemorySize == 1) {
                            printErrorLine(ARITHMETIC_ERROR_MESSAGE, line, ARITHMETIC_ERROR_CODE);
                        }


                        if (isNumber(toAnalyze[line].opcode[2])) {                               // add value
                            *(mainMemory + currentByte) += (toAnalyze[line].opcode[2] - '0');
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'N') {                           // add the value of the next memory cell
                            if (currentByte != (mainMemorySize - 1)) {
                                *(mainMemory + currentByte) += *(mainMemory + currentByte + 1);
                            }

                            break;
                        } else if (toAnalyze[line].opcode[2] == 'P') {                           // add the value of the previous memory cell
                            if (currentByte != 0) {
                                *(mainMemory + currentByte) += *(mainMemory + currentByte - 1);
                            }

                            break;
                        }

                        wrongOpcode
                    
                    case 'P':
                        // prevent the user from adding the value of the current cell to the current cell
                        if (toAnalyze[line].opcode[2] == '0') {
                            printErrorLine(WRONG_VALUE_ERROR_MESSAGE, line, WRONG_VALUE_ERROR_CODE)
                        }


                        // add in a user safe way the value of the requested cell
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            if ((toAnalyze[line].opcode[2] - '0') > currentByte) {
                                *(mainMemory + currentByte) += *mainMemory;

                                break;
                            } 
                            
                            *(mainMemory + currentByte) += *(mainMemory + currentByte - (toAnalyze[line].opcode[2] - '0'));
                            break;
                        }
                        
                        wrongOpcode

                    case 'N':
                        // prevent the user from adding the value of the current cell to the current cell
                        if (toAnalyze[line].opcode[2] == '0') {
                            printErrorLine(WRONG_VALUE_ERROR_MESSAGE, line, WRONG_VALUE_ERROR_CODE)
                        }


                        // add in a user safe way the value of the requested cell
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            if ((toAnalyze[line].opcode[2] - '0') > (mainMemorySize - currentByte)) {
                                *(mainMemory + currentByte) += *(mainMemory + (mainMemorySize - 1));

                                break;
                            } 
                         
                            *(mainMemory + currentByte) += *(mainMemory + currentByte + (toAnalyze[line].opcode[2] - '0'));
                            break;
                        }
                        
                        wrongOpcode
                    
                    default:
                        wrongOpcode
                }

                break;

            case 'C':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'P':
                        // copy the value of the next or previous memory cell to the current memory cell in the main memory

                        if (toAnalyze[line].opcode[2] == 'N') {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte + 1);
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'P') {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte - 1);
                            break;
                        }

                        wrongOpcode
                    
                    case 'M':
                        // conditional statements

                        if (toAnalyze[line].opcode[2] == 'T') {
                            line = *(mainMemory + currentByte) == 0 ? (line + 1) : line;
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'F') {
                            line = *(mainMemory + currentByte) != 0 ? (line + 1) : line;
                            break;
                        }

                        wrongOpcode

                    case 'L':
                        // searches all function names and if it finds the function it will go the the line + 1 the 
                        // the function was declared

                        for (unsigned int i = 0; i < totalFunctions; i++) {
                            if (*(functionName + i) == toAnalyze[line].opcode[2]) {
                                lineCalled = line;
                                line = *(functionLine + i);
                                foundFunction = TRUE;

                                break;
                            }
                        }

                        if (foundFunction == TRUE) {
                            foundFunction = FALSE;
                            break;
                        }

                        printErrorLine(WRONG_ARGUMENT_ERROR_MESSAGE, line, WRONG_ARGUMENT_ERROR_CODE)

                    default:
                        wrongOpcode
                }

                break;

            case 'D':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'I':
                        // display the value of the current memory cell as a character

                        if (toAnalyze[line].opcode[2] == 'S') {
                            printf("%c", *(mainMemory + currentByte));
                            break;
                        }
                        
                        wrongOpcode

                    case 'E':
                        // decrease the value of the current memory cell by one

                        if (toAnalyze[line].opcode[2] == 'C') {
                            *(mainMemory + currentByte) -= 1;
                            break;
                        }
                        
                        wrongOpcode
                        
                    case 'V':
                        // divide the value of the current cell and save the result back to memory

                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte) / (toAnalyze[line].opcode[2] - '0');
                            break;
                        } 

                        wrongOpcode
                    
                    case 'S':
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            for (int i = 0; i <= (toAnalyze[line].opcode[2] - '0'); i++) {
                                printf("%c", *(mainMemory + i));
                            }

                            break;
                        }

                        printErrorLine(WRONG_ARGUMENT_ERROR_MESSAGE, line, WRONG_ARGUMENT_ERROR_CODE)
                        wrongOpcode

                    default:
                        wrongOpcode
                }

                break;

            case 'E':
                switch (toAnalyze[line].opcode[1]) {
                    case 'A':
                        // adds a number to the current cell from the given number or from the next - previous cell from
                        // extended memory

                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(extendedMemory + extendedCurrentByte) += toAnalyze[line].opcode[2] - '0';
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'N') {
                            *(extendedMemory + extendedCurrentByte) += *(extendedMemory + extendedCurrentByte + 1);
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'P') {
                            *(extendedMemory + extendedCurrentByte) += *(extendedMemory + extendedCurrentByte - 1);
                            break;
                        }

                        wrongOpcode

                    case 'M':
                        switch (toAnalyze[line].opcode[2]) {
                            case 'N':
                                // moves the "pointer" used for extended memory to the next position, if there is no
                                // more cells left in the extended memory it will create one more cell

                                extendedCurrentByte++;

                                if (extendedCurrentByte == extendedMemorySize) {
                                    extendedMemory = realloc(extendedMemory, (extendedMemorySize + 1) * sizeof(short));
                                    *(extendedMemory + extendedMemorySize + 1) = 0;
                                    extendedMemorySize++;
                                }

                                break;
                            
                            case 'P':
                                extendedCurrentByte = extendedCurrentByte == 1 ? 1 : (extendedCurrentByte - 1);
                                break;
                            
                            case 'I':
                                (*(extendedMemory + extendedCurrentByte))++;
                                break;
                            
                            case 'D':
                                (*(extendedMemory + extendedCurrentByte))--;
                                break;
                            
                            case 'S':
                                printf("%i", *(extendedMemory + extendedCurrentByte));
                                break;
                            
                            case 'G':
                                *(extendedMemory + extendedCurrentByte) = getchar(); getchar();
                                break;

                            default:
                                // multiplication for the extended memory

                                if (isNumber(toAnalyze[line].opcode[2])) {
                                    *(extendedMemory + extendedCurrentByte) *= toAnalyze[line].opcode[2] - '0';
                                    break;
                                } else if (toAnalyze[line].opcode[2] == 'N') {
                                    *(extendedMemory + extendedCurrentByte) *= *(extendedMemory + extendedCurrentByte + 1);
                                    break;
                                } else if (toAnalyze[line].opcode[2] == 'P') {
                                    *(extendedMemory + extendedCurrentByte) *= *(extendedMemory + extendedCurrentByte - 1);
                                    break;
                                }

                                wrongOpcode
                        }

                        break;

                    case 'S':
                        // subtraction for the extended memory

                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(extendedMemory + extendedCurrentByte) -= toAnalyze[line].opcode[2] - '0';
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'N') {
                            *(extendedMemory + extendedCurrentByte) -= *(extendedMemory + extendedCurrentByte + 1);
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'P') {
                            *(extendedMemory + extendedCurrentByte) -= *(extendedMemory + extendedCurrentByte - 1);
                            break;
                        }

                        wrongOpcode

                    case 'P':
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(extendedMemory + extendedCurrentByte) = power(*(extendedMemory + currentByte), toAnalyze[line].opcode[2] - '0');
                            break;
                        }

                        wrongOpcode

                    case 'N':
                        if (toAnalyze[line].opcode[2] == 'D') {
                            return 0;
                        }

                        wrongOpcode

                    default:
                        wrongOpcode
                }

                break;

            case 'F':
                if (toAnalyze[line].opcode[1] == 'N') {
                    // searches if the function name already exists
                    for (unsigned int i = 0; i < totalFunctions; i++) {
                        if (*(functionName + i) == toAnalyze[line].opcode[2]) {
                            foundFunction = TRUE;
                        }
                    }

                    if (foundFunction == TRUE) {
                        foundFunction = FALSE;
                        break;
                    }

                    // allocates more memory for the next function
                    functionName = realloc(functionName, (totalFunctions + 1));
                    functionLine = realloc(functionLine, (totalFunctions + 1) * sizeof(int));
                    
                    // saves all data necessary for the possible CL* command
                    *(functionName + totalFunctions) = toAnalyze[line].opcode[2];
                    *(functionLine + totalFunctions) = line;

                    totalFunctions++;

                    // searches all lines for the RET command 
                    for (unsigned int i = line; i < totalLines; i++) {
                        if ((toAnalyze[i].opcode[0] == 'R') && (toAnalyze[i].opcode[1] == 'E') && (toAnalyze[i].opcode[2] == 'T')) {
                            line = i;
                            break;
                        }
                    }
                    
                    break;
                }

                wrongOpcode

            case 'G':
                switch (toAnalyze[line].opcode[1]) {
                    case 'E':
                        // get input from the user and save it to main memory

                        if (toAnalyze[line].opcode[2] == 'T') {
                            *(mainMemory + currentByte) = getchar(); getchar();

                            break;
                        }

                        wrongOpcode

                    case 'O':
                        // searches the corresponding label

                        for (unsigned int i = 0; i < totalLabels; i++) {
                            if (*(labelName + i) == toAnalyze[line].opcode[2]) {
                                line = *(labelLine + i);
                                foundLabel = TRUE;

                                break;
                            }
                        }

                        if (foundLabel == TRUE) {
                            foundLabel = FALSE;
                            break;
                        }

                        wrongOpcode

                    default:
                        wrongOpcode
                }

                break;

            case 'I':
                switch (toAnalyze[line].opcode[1]) {
                    case 'N':
                        // increases the value of the current memory cell by one

                        if (toAnalyze[line].opcode[2] == 'C') {
                            (*(mainMemory + currentByte))++;
                            break;
                        }

                        wrongOpcode
                    
                    default:
                        wrongOpcode
                }

                break;

            case 'L':
                if (toAnalyze[line].opcode[1] == 'B') {
                    // searches if a label with the same name already exists
                    for (unsigned int i = 0; i < totalLabels; i++) {
                        if (*(labelName + i) == toAnalyze[line].opcode[2]) {
                            foundLabel = TRUE;
                        }
                    }

                    if (foundLabel == TRUE) {
                        foundLabel = FALSE;
                        break;
                    }

                    // allocates memory for the next possible label
                    labelName = realloc(labelName, (totalLabels + 1));
                    labelLine = realloc(labelLine, (totalLabels + 1) * sizeof(int));

                    // saves all the necessary data for the possible GO* command
                    *(labelName + totalLabels) = toAnalyze[line].opcode[2];
                    *(labelLine + totalLabels) = line;
                    
                    totalLabels++;

                    break;
                }

                wrongOpcode

            case 'M':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'V':
                        // save the value to the current memory cell
                        *(mainMemory + currentByte) = toAnalyze[line].opcode[2];
                        
                        break;
                    
                    case 'L':
                        // multiplication for the main memory

                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(mainMemory + currentByte) *= (toAnalyze[line].opcode[2] - '0');
                            break;
                        }

                        wrongOpcode
                    
                    case 'M':
                        // assigns the same value for all memory cells in the main memory

                        for (int i = 0; i < mainMemorySize - 1; i++) {
                            *(mainMemory + i) = toAnalyze[line].opcode[2];
                        }

                        break;

                    default:
                        wrongOpcode
                }

                break;

            case 'N':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'W':
                        // create a new line in the terminal 

                        if (toAnalyze[line].opcode[2] == 'L') {
                            printf("\n");
                            break;
                        }
                        
                        wrongOpcode
                    
                    case 'E':
                        // go to the next byte in the list, if the current memory cell is at the last possible position
                        // of the list then expand the list by one 

                        if (toAnalyze[line].opcode[2] == 'X') {
                            currentByte++;

                            if (currentByte == mainMemorySize) {
                                mainMemory = realloc(mainMemory, (mainMemorySize + 1));
                                *(mainMemory + currentByte) = *(mainMemory + currentByte + 1) = 0;
                                mainMemorySize++;
                            }

                            break;
                        }

                        wrongOpcode

                    default:
                        wrongOpcode
                }

                break;

            case 'P':
                switch (toAnalyze[line].opcode[1])
                {
                    case 'R':
                        // go to the previous cell on the list

                        if (toAnalyze[line].opcode[2] == 'E') {
                            currentByte = currentByte == 1 ? currentByte : (currentByte - 1);
                            break;
                        }
                        
                        wrongOpcode

                    case 'F':
                        // this is the NEX statement but easier to use if we need to skip large amount of values in the
                        // list at once


                        if (isNumber(toAnalyze[line].opcode[2])) {
                            currentByte += (toAnalyze[line].opcode[2] - '0');

                            if (currentByte >= mainMemorySize) {
                                mainMemory = realloc(mainMemory, (currentByte - mainMemorySize) + 1);

                                for (int i = 0; i < (currentByte - mainMemorySize + 1); i++) {
                                    *(mainMemory + mainMemorySize + i) = 0;
                                }

                                mainMemorySize += (currentByte - mainMemorySize) + 1;
                            }

                            break;
                        }
                        
                        printErrorLine(WRONG_ARGUMENT_ERROR_MESSAGE, line, WRONG_ARGUMENT_ERROR_CODE);

                    case 'B':
                        // this is the PRE statement but easier to use if we need to skip large amount of values in the
                        // list at once


                        if (isNumber(toAnalyze[line].opcode[2])) {
                            currentByte -= (toAnalyze[line].opcode[2] - '0');

                            if (currentByte < 0) {
                                currentByte = 0;
                            }

                            break;
                        }
                        
                        printErrorLine(WRONG_ARGUMENT_ERROR_MESSAGE, line, WRONG_ARGUMENT_ERROR_CODE);
                    
                    case 'W':
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(mainMemory + currentByte) = power(*(mainMemory + currentByte), toAnalyze[line].opcode[2] - '0');
                            break;
                        }

                        wrongOpcode
                    
                    default:
                        wrongOpcode
                }

                break;

            case 'R':
                switch (toAnalyze[line].opcode[1]) {
                    case 'R':
                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte) % (toAnalyze[line].opcode[2] - '0');
                            break;
                        }

                        wrongOpcode
                    
                    case 'E':
                        if (toAnalyze[line].opcode[2] == 'T') {
                            line = lineCalled;
                            //exit(0);
                            break;
                        }

                        wrongOpcode

                    default:
                        wrongOpcode
                }

                break;

            case 'S':
                switch (toAnalyze[line].opcode[1]) {
                    case 'H':
                        // shift operators for the main memory

                        if (toAnalyze[line].opcode[2] == 'R') {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte) >> 1;
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'L') {
                            *(mainMemory + currentByte) = *(mainMemory + currentByte) << 1;
                            break;
                        }

                        wrongOpcode

                    case 'U':
                        // subtraction for the main memory

                        if (isNumber(toAnalyze[line].opcode[2])) {
                            *(mainMemory + currentByte) -= toAnalyze[line].opcode[2] - '0';
                            break;
                        } else if (toAnalyze[line].opcode[2] == 'N') {
                            if (currentByte != (mainMemorySize - 1)) {
                                *(mainMemory + currentByte) -= *(mainMemory + currentByte + 1);
                            }

                            break;
                        } else if (toAnalyze[line].opcode[2] == 'P') {
                            if (currentByte != 0) {
                                *(mainMemory + currentByte) -= *(mainMemory + currentByte - 1);
                            }

                            break;
                        }

                        wrongOpcode

                    default:
                        wrongOpcode
                }
                
                break;

            default:
                wrongOpcode
        }
    }

    return 0;
}

#pragma endregion funcs