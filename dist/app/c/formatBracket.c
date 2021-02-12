#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceNewline(char **input, char **output);
void addIndent(char **output, const int *indentLevelPtr);
void formatBracket(char **input, char **output, int *indentLevelPtr, int firstCharCheck);
int main(int argc, char **argv) {
    FILE *fptr;
    if (argc == 2) {
        fptr = fopen(argv[1], "r");
    } else {
        fptr = stdin;
    }
    char input[8192];
    char output[8192];
    char concat[8192] = {'\0'};
    while (fgets(input, sizeof(char) * 8192, fptr) != NULL) {
        strcat(concat, input);
    }
    fclose(fptr);
    char *outputPtr = output;
    char *inputPtr = concat;
    int indentLevel = 0;
    int *indentlevelPtr = &indentLevel;
    int firstCheckChar = 0;
    while (*inputPtr) {
        formatBracket(&inputPtr, &outputPtr, indentlevelPtr, firstCheckChar);
        *outputPtr++ = *inputPtr++;
    }
    *outputPtr = '\0';
    printf("%s", output);
}
void replaceNewline(char **input, char **output) {
    if (**input != '\n') {
        *(*output)++ = '\n';  // todo
    }
}
void addIndent(char **output, const int *indentlevelPtr) {
    for (int i = 0; i < *indentlevelPtr; i++) {
        *(*output)++ = ' ';
        *(*output)++ = ' ';
    }
}
void formatBracket(char **input, char **output, int(*indentLevelPtr), int firstCharCheck) {
    while (*(*input)) {
        if (firstCharCheck != 1) {
            *(*output)++ = *(*input)++;
            firstCharCheck = 1;
            continue;
        }
        if (*(*input) == '{') {
            if (*(*input - 1) == '\'' || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                firstCharCheck = 1;
                continue;
            }
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addIndent(output, indentLevelPtr);  //根據indentlevel進行縮排處理
            *(*output)++ = *(*input)++;
            firstCharCheck = 1;
            replaceNewline(input, output);
            (*indentLevelPtr)++;  // indentlevel + 1
            formatBracket(input, output, indentLevelPtr, firstCharCheck);
        }

        if (*(*input) == '}') {
            if ((*(*input - 1) == '\'') || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                firstCharCheck = 1;
                continue;
            }
            (*indentLevelPtr)--;  // indentlevel - 1
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addIndent(output, indentLevelPtr);
            *(*output)++ = *(*input)++;
            firstCharCheck = 1;
            replaceNewline(input, output);
            return;
        }
        if (*((*output) - 1) == '\n') {
            addIndent(output, indentLevelPtr);
        }
        if (*(*input) == ';' && *(*input + 1) != '\n') {
            if (*(*input - 1) == ';' || *(*input) + 1 == ';') {
                *(*output)++ = *(*input)++;
                firstCharCheck = 1;
                continue;
            }
            *(*output)++ = *(*input)++;
            firstCharCheck = 1;
            *(*output)++ = '\n';
            continue;
        }

        *(*output)++ = *(*input)++;
        firstCharCheck = 1;
    }
}
