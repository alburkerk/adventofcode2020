#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINES 4000
#define BITMASK_SIZE 36
#define MEM_SIZE 100000

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int input[MAX_LINES];
    int i = 0;
    uint64_t _1mask = 0;
    uint64_t _0mask = 0;
    uint64_t mem[MEM_SIZE] = {0};
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (line[1] == 'a')
        {
            char* delimiter = " ";
            char* token = strtok(line, delimiter);
            token = strtok(NULL, delimiter);
            token = strtok(NULL, delimiter);
            _0mask = 0xffffffffff;
            _1mask = 0x0000000000;

            for (int j = 0; j < BITMASK_SIZE; j++)
            {
                if (token[j] == '0')
                {
                    _0mask &= ~(1ULL << (BITMASK_SIZE - j - 1));
                }

                if (token[j] == '1')
                {
                    _1mask |= 1ULL << (BITMASK_SIZE - j - 1);
                }
            }

            strtok(NULL, delimiter);
        }
        else
        {
            char* delimiter = " []";
            char* token = strtok(line, delimiter);
            token = strtok(NULL, delimiter);
            int index = strtol(token, NULL, 10);
            strtok(NULL, delimiter);
            token = strtok(NULL, delimiter);
            uint64_t val = strtol(token, NULL, 10);
            mem[index] = (val | _1mask) & _0mask;
        }

        i++;
    }

    uint64_t sum = 0;

    for (int i = 0; i < MEM_SIZE; i++)
    {
        sum += mem[i];
    }

    printf("solution : %llu\n", sum);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
