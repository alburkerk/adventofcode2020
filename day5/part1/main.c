#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LINES 4000

uint16_t getSeatId(const char* seat)
{
    uint16_t row = 0;
    uint16_t column = 0;

    for (uint16_t i = 0; i < 7; i++)
    {
        row |= (seat[i] == 'B' ? 1u : 0u) << (6 - i);
    }

    for (uint16_t i = 0; i < 3 ; i++)
    {
        column |= (seat[i + 7] == 'R' ? 1u : 0u) << (2 - i);
    }

    return row * 8 + column;
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

    uint16_t max = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        uint16_t id = getSeatId(line);

        if (id > max)
        {
            max = id;
        }
    }

    printf("solution is %u\n", max);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
