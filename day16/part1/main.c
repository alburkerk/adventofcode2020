#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RANGE_VALUE 4000
uint8_t validMap[MAX_RANGE_VALUE] = { 0 };

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int stage = 0;
    uint32_t error = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strlen(line) == 1)
        {
            stage++;
            i = 0;
            continue;
        }

        if (stage == 0)
        {
            char* delimiter = ":-";
            char* token = strtok(line, delimiter);
            char* delimiter2 = "- ";
            token = strtok(NULL, delimiter2);
            uint32_t range1 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            uint32_t range2 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            token = strtok(NULL, delimiter2);
            uint32_t range3 = strtol(token, NULL, 10);
            token = strtok(NULL, delimiter2);
            uint32_t range4 = strtol(token, NULL, 10);
            int j = range1;

            while (j <= range2)
            {
                validMap[j] = 1;
                j++;
            }

            j = range3;

            while (j <= range4)
            {
                validMap[j] = 1;
                j++;
            }
        }

        if (stage == 2)
        {
            if (memcmp(line, "nearby", 5) == 0)
            {
                continue;
            }

            char* delimiter = ",";
            char* token = strtok(line, delimiter);

            while (token != NULL)
            {
                if (!validMap[strtol(token, NULL, 10)])
                {
                    error += strtol(token, NULL, 10);
                }

                token = strtok(NULL, delimiter);
            }
        }
    }

    printf("solution : %d\n", error);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
