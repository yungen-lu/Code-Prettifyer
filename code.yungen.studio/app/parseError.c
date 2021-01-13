#include <regex.h>
#include <stdio.h>
#include <string.h>

int removeLine(char* string);
void removeNewline(char* string);
void replaceInfo(char* string);
int main() {
    char input[1024];
    regex_t regexCompile;
    char* pattern = "[^ ]+:([0-9]+):([0-9]+):[\r\n\t\f\v ]+([^:]+):[\r\n\t\f\v ]+(.+)\\[+(.+)\\]";  // 定義表示式
    int groupCnt = 6;
    regmatch_t groupArray[groupCnt];  //匹配後的結果存放在這裏
    int lineCnt = 0;
    int checkCnt = 0;
    if (regcomp(&regexCompile, pattern, REG_EXTENDED)) {  //將表示式編譯成特定的資料格式
        printf("Could not compile regular expression.\n");
        return -1;
    }

    while (fgets(input, sizeof(char) * 1024, stdin) != NULL) {
        if (removeLine(input) == 1) {
            continue;
        }
        removeNewline(input);
        lineCnt++;
        if (regexec(&regexCompile, input, groupCnt, groupArray, 0) == 0) {  //對input進行匹配
            checkCnt++;
            unsigned int g = 1;
            for (g = 1; g < groupCnt; g++) {
                char sourceCopy[strlen(input) + 1];
                strcpy(sourceCopy, input);
                sourceCopy[groupArray[g].rm_eo] =
                    '\0';  //在sourcCopy為原始資料的複製，將groupArray[g].rm_eo（第g個Group的結束位址）（rm_so,rm_eo是regmatch_t
                           //struct的其中兩個參數，紀錄匹配結果開始與結束位址）位址賦予'\0'
                if (g == 3) {  //對第三個Group進行處理（錯誤類別）轉換為toastr模組能參數
                    replaceInfo(sourceCopy + groupArray[g].rm_so);
                }
                printf("%s#", sourceCopy + groupArray[g].rm_so);  // sourceCopy 位址加上groupArray[g].rm_so（開始位址）等於第g個Group的字串起始位址
            }
            printf("?");
        }
    }
    if ((checkCnt == 0) && (lineCnt == 0)) { //如果沒有錯誤的話輸出此行
        printf("success# #?");
    }
    regfree(&regexCompile); //清空 regexCompile的内容
}
int removeLine(char* string) {
    if (strncmp(string, "Checking", 8) == 0) {
        return 1;
    }
    return 0;
}
void removeNewline(char* string) {
    char* ptr = strchr(string, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}
void replaceInfo(char* string) {
    if (strcmp(string, "style") == 0) {
        strcpy(string, "info");
    }
    if (strcmp(string, "performance") == 0) {
        strcpy(string, "info");
    }
    if (strcmp(string, "portability") == 0) {
        strcpy(string, "info");
    }
    if (strcmp(string, "information") == 0) {
        strcpy(string, "info");
    }
}