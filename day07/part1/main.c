#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_LINES 600
#define MAX_COLOR_LENGTH 30
#define MAX_BAGS_PER_COLOR 50
#define MAX_GROUPS 5

typedef struct Bag Bag;

struct Bag
{
    char color[MAX_COLOR_LENGTH];
    Bag* contains[MAX_BAGS_PER_COLOR];
};

regex_t containsRegex;
regex_t singleColorRegex;
regmatch_t regGroups[MAX_GROUPS];
Bag bags[MAX_LINES];

void addSubColor(char* color, char* subColor)
{
    int subColorIndex = 0;

    for (; subColorIndex < MAX_LINES; subColorIndex++)
    {
        if (strcmp(bags[subColorIndex].color, subColor) == 0)
        {
            break;
        }

        // subcolor does not exist
        if (strlen(bags[subColorIndex].color) == 0)
        {
            strcpy(bags[subColorIndex].color, subColor);
            break;
        }
    }

    for (int i = 0; i < MAX_LINES; i++)
    {
        // color not added yet in list
        if (strlen(bags[i].color) == 0)
        {
            strcpy(bags[i].color, color);
        }

        if (strcmp(bags[i].color, color) == 0)
        {
            for (int j = 0; j < MAX_BAGS_PER_COLOR; j++)
            {
                if (bags[i].contains[j] == NULL)
                {
                    bags[i].contains[j] = &bags[subColorIndex];
                    return;
                }
            }

            printf("ERROR MAX_BAGS_PER_COLOR too small\n");
            exit(-1);
        }
    }
}

int canContainShinyGold(Bag* bag)
{
    if (bag == NULL || strlen(bag->color) == 0)
    {
        return 0;
    }

    if (strcmp(bag->color, "shiny gold") == 0)
    {
        return 1;
    }

    for (int i = 0; i < MAX_BAGS_PER_COLOR; i++)
    {
        if (canContainShinyGold(bag->contains[i]))
        {
            return 1;
        }
    }

    return 0;
}

void debugBags()
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (strlen(bags[i].color) == 0)
        {
            break;
        }

        printf("color : %s\n", bags[i].color);

        for (int j = 0; j < MAX_BAGS_PER_COLOR; j++)
        {
            if (bags[i].contains[j] == NULL)
            {
                break;
            }

            printf("  - %s\n", bags[i].contains[j]->color);
        }

        printf("\n");
    }
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int input[MAX_LINES];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    if (regcomp(&containsRegex, "(([[:lower:]]+[ ]{0,1})+)( bags\\ contain)",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    if (regcomp(&singleColorRegex, "[[:digit:]]\\ ([[:lower:] ]+)\\ bag",
                REG_EXTENDED))
    {
        printf("error while compiling regex\n");
    }

    // clean
    for (int i = 0; i < MAX_LINES; i++)
    {
        bags[i].color[0] = '\0';

        for (int j = 0; j < MAX_BAGS_PER_COLOR; j++)
        {
            bags[i].contains[j] = NULL;
        }
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (!regexec(&containsRegex, line, MAX_GROUPS, regGroups, 0))
        {
            char strValue[MAX_COLOR_LENGTH];
            char delimiter[] = ",";
            strncpy(strValue, line + regGroups[1].rm_so,
                    regGroups[1].rm_eo - regGroups[1].rm_so);
            strValue[regGroups[1].rm_eo] = '\0';
            char* color = strtok(line + regGroups[3].rm_eo, delimiter);

            while (color != NULL)
            {
                if (!regexec(&singleColorRegex, color, MAX_GROUPS, regGroups, 0))
                {
                    char parsedColor[MAX_COLOR_LENGTH] = "";
                    strncpy(parsedColor, color + regGroups[1].rm_so, regGroups[1].rm_eo - regGroups[1].rm_so);
                    addSubColor(strValue, parsedColor);
                }

                color = strtok(NULL, delimiter);
            }
        }

        i++;
    }

    // count bags colros than can contain shiny gold
    int count = 0;

    for (int i = 0; i < MAX_LINES; i++)
    {
        // skip the shiny gold bag itself
        if (strcmp(bags[i].color, "shiny gold") == 0)
        {
            continue;
        }

        count += canContainShinyGold(&bags[i]);
    }

    printf("number of bags that can contain shiny gold : %d\n", count);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
