#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeNewline(const char *a);
char *removeSpace(const char *string);
void replaceTab(const char *string);
int main() {
    char input[128];
    while (fgets(input, 128, stdin) != NULL) {
        if (input[0] == '\n') {
            continue;
        }
        removeNewline(input);
        replaceTab(input);
        char *ptr = removeSpace(input);
        printf("%s\n", ptr);
        free(ptr);
    }
}
void removeNewline(const char *a) {
    char *b = strchr(a, '\n');
    if (b) {
        *b = '\0';
    }
}
char *removeSpace(const char *string) {
    const char *ptr = string;  // ptr作為讀取資料的指標
    char *out = malloc(sizeof(char) * strlen(string) + 1);
    char *qtr = out;  // qtr作為寫入資料的指標
    while (*ptr == ' ') {
        ptr++;
    }
    while (*ptr) {
        while ((*ptr == ' ') && *(ptr + 1) == ' ') {  //若重複找到空白ptr向前跳過
            ptr++;
        }
        *qtr++ = *ptr++;  //遇到正常字元則依序寫入
    }
    if ((*(ptr - 1) == ' ') && qtr != out) {  //防止out of bound memory access
        qtr--;
    }
    *qtr = '\0';
    printf("%ld\n", ptr - string);
    return out;
}
void replaceTab(const char *string) {
    char *qtr;
    while ((qtr = strchr(string, '\t')) != NULL) {  //尋找到\t後替換為空白
        *qtr = ' ';
    }
}
