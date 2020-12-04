#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000

int isValid(const char* data) {
    if(strstr(data, "byr:") != NULL && 
        strstr(data, "iyr:") != NULL && 
        strstr(data, "eyr:") != NULL && 
        strstr(data, "hgt:") != NULL && 
        strstr(data, "hcl:") != NULL && 
        strstr(data, "ecl:") != NULL &&
        strstr(data, "pid:") != NULL)
            return 1;

    return 0;
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    int validPassportCount = 0;
    char currentPassport[400] = "";

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strlen(line) == 1) {
            validPassportCount += isValid(currentPassport);
            currentPassport[0] = '\0';
        }
        else {
            strncat(currentPassport, line, len);
        }
    }

    // count last passport
    validPassportCount += isValid(currentPassport);

    printf("good passport count : %d\n", validPassportCount);

    if (line)
        free(line);

    fclose(fp);
}
