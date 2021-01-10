#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceNewline(char **input, char **output) {
    if (**input != '\n') {
        *(*output)++ = '\n';  // todo
    }
}
void addindent(char **output, int *indentlevelPtr) {
    for (int i = 0; i < (*indentlevelPtr); i++) {
        *(*output)++ = ' ';
        *(*output)++ = ' ';
    }
}
void formatBracket(char **input, char **output, int(*indentlevelPtr)) {
    while (*(*input)) {
        if (*(*input) == '{') {
            if (*(*input - 1) == '\'' || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                continue;
            }
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addindent(output, indentlevelPtr);  //根據indentlevel進行縮排處理
            *(*output)++ = *(*input)++;
            replaceNewline(input, output);
            (*indentlevelPtr)++;  //indentlevel + 1
            formatBracket(input, output, indentlevelPtr);
        }

        if (*(*input) == '}') {
            if (*(*input - 1) == '\'' || *(*input) + 1 == '\'') {
                *(*output)++ = *(*input)++;
                continue;
            }
            (*indentlevelPtr)--;  //indentlevel - 1
            if ((*(*input - 1)) != '\n') {
                *(*output)++ = '\n';  // todo
            }
            addindent(output, indentlevelPtr);
            *(*output)++ = *(*input)++;
            replaceNewline(input, output);
            return;
        }
        if (*((*output) - 1) == '\n') {
            addindent(output, indentlevelPtr);
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
    while (fgets(input, sizeof(char) * 1024, fptr) != NULL) {
        strcat(concat, input);
    }
    char *outputPtr = output;
    char *inputPtr = concat;
    int indentlevel = 0;
    int *indentlevelPtr = &indentlevel;
    while (*inputPtr) {
        formatBracket(&inputPtr, &outputPtr, indentlevelPtr);
        *outputPtr++ = *inputPtr++;
    }
    *outputPtr = '\0';
    printf("%s", output);
}
