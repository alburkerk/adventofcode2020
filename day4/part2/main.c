#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINES 4000
#define MAX_GROUPS 3

regex_t byrRegex;
regex_t iyrRegex;
regex_t eyrRegex;
regex_t hgtRegex;
regex_t hclRegex;
regex_t eclRegex;
regex_t pidRegex;

int isValid(const char* data)
{
    if (!(strstr(data, "byr:") != NULL &&
          strstr(data, "iyr:") != NULL &&
          strstr(data, "eyr:") != NULL &&
          strstr(data, "hgt:") != NULL &&
          strstr(data, "hcl:") != NULL &&
          strstr(data, "ecl:") != NULL &&
          strstr(data, "pid:") != NULL))
    {
        return 0;
    }

    regmatch_t regGroups[MAX_GROUPS];
    int value = 0;

    // match
    if (!regexec(&byrRegex, data, 0, NULL, 0))
    {
        char* pos = strstr(data, "byr:");
        char strValue[10];
        memcpy(strValue, pos + 4, 4);
        strValue[4] = '\0';
        value = strtol(strValue, NULL, 10);

        if (value < 1920 || value > 2002)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    // match
    if (!regexec(&iyrRegex, data, 0, NULL, 0))
    {
        char* pos = strstr(data, "iyr:");
        char strValue[10];
        memcpy(strValue, pos + 4, 4);
        strValue[4] = '\0';
        value = strtol(strValue, NULL, 10);

        if (value < 2010 || value > 2020)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    // match
    if (!regexec(&eyrRegex, data, 0, NULL, 0))
    {
        char* pos = strstr(data, "eyr:");
        char strValue[10];
        memcpy(strValue, pos + 4, 4);
        strValue[4] = '\0';
        value = strtol(strValue, NULL, 10);

        if (value < 2020 || value > 2030)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    // match
    if (!regexec(&hgtRegex, data, MAX_GROUPS, regGroups, 0))
    {
        char strValue[10];
        strncpy(strValue, data + regGroups[1].rm_so,
                regGroups[1].rm_eo - regGroups[1].rm_so);
        strValue[ regGroups[1].rm_eo - regGroups[1].rm_so ] = '\0';
        value = strtol(strValue, NULL, 10);

        // cm
        if (data[regGroups[2].rm_so] == 'c' && (value < 150 || value > 193))
        {
            return 0;
        }

        // in
        if (data[regGroups[2].rm_so] == 'i' && (value < 59 || value > 76))
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    if (regexec(&hclRegex, data, 0, NULL, 0))
    {
        return 0;
    }

    if (regexec(&eclRegex, data, 0, NULL, 0))
    {
        return 0;
    }

    if (regexec(&pidRegex, data, 0, NULL, 0))
    {
        return 0;
    }

    return 1;
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    // compile regex
    if (regcomp(&byrRegex, "byr:[[:digit:]]{4}[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&iyrRegex, "iyr:[[:digit:]]{4}[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&eyrRegex, "eyr:[[:digit:]]{4}[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&hgtRegex, "hgt:([[:digit:]]{2,3})((cm|in))[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&hclRegex, "hcl:#[0-9a-f]{6}[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&eclRegex, "ecl:(amb|blu|brn|gry|grn|hzl|oth)[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&pidRegex, "pid:[[:digit:]]{9}[[:space:]]",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    int validPassportCount = 0;
    char currentPassport[400] = "";

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strlen(line) == 1)
        {
            validPassportCount += isValid(currentPassport);
            currentPassport[0] = '\0';
        }
        else
        {
            strncat(currentPassport, line, len);
        }
    }

    // count last passport
    validPassportCount += isValid(currentPassport);
    printf("good passport count : %d\n", validPassportCount);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
