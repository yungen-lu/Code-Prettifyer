#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceNewline(char **input, char **output);
void addIndent(char **output, int *indentLevelPtr);
void formatBracket(char **input, char **output, int *indentLevelPtr);
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
    char *outputPtr = output;
    char *inputPtr = concat;
    int indentLevel = 0;
    int *indentlevelPtr = &indentLevel;
    while (*inputPtr) {
        formatBracket(&inputPtr, &outputPtr, indentlevelPtr);
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
void addIndent(char **output, int *indentlevelPtr) {
    for (int i = 0; i < *indentlevelPtr; i++) {
        *(*output)++ = ' ';
        *(*output)++ = ' ';
    }
}
void formatBracket(char **input, char **output, int(*indentLevelPtr)) {
    while (*(*input)) {
        if (*(*input) == '{') {
            if (*(*input - 1) == '\'' || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                continue;
            }
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addIndent(output, indentLevelPtr);  //根據indentlevel進行縮排處理
            *(*output)++ = *(*input)++;
            replaceNewline(input, output);
            (*indentLevelPtr)++;  // indentlevel + 1
            formatBracket(input, output, indentLevelPtr);
        }

        if (*(*input) == '}') {
            if (*(*input - 1) == '\'' || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                continue;
            }
            (*indentLevelPtr)--;  // indentlevel - 1
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addIndent(output, indentLevelPtr);
            *(*output)++ = *(*input)++;
            replaceNewline(input, output);
            return;
        }
        if (*((*output) - 1) == '\n') {
            addIndent(output, indentLevelPtr);
        }
        if (*(*input) == ';' && *(*input + 1) != '\n') {
            if (*(*input - 1) == ';' || *(*input) + 1 == ';') {
                *(*output)++ = *(*input)++;
                continue;
            }
            *(*output)++ = *(*input)++;
            *(*output)++ = '\n';
            continue;
        }

        *(*output)++ = *(*input)++;
    }
}
