#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 3
#define MAX_BUSES 200

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char input[MAX_LINES][MAX_BUSES];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        strcpy(input[i], line);
        i++;
    }

    int readyTimestamp = strtol(input[0], NULL, 10);
    int busIds[MAX_BUSES] = { 0 };
    char delimiter[] = ",";
    int k = 0;
    char* token = strtok(input[1], delimiter);

    while (token != NULL)
    {
        if (strcmp(token, "x"))
        {
            busIds[k] = strtol(token, NULL, 10);
            k++;
        }

        token = strtok(NULL, delimiter);
    }

    int minTime = 2 * readyTimestamp;
    int minId = 0;

    for (int j = 0; j < k; j++)
    {
        int tmp = 0;

        while (tmp < readyTimestamp)
        {
            tmp += busIds[j];
        }

        if (tmp < minTime)
        {
            minTime = tmp;
            minId = busIds[j];
        }
    }

    printf("solution : %d\n", (minTime - readyTimestamp) * minId);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
