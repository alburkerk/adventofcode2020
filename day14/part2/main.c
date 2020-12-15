#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINES 4000
#define BITMASK_SIZE 36
#define MEM_SIZE 100000
#define MAX_DIFFERENT_ADDR 100000

uint64_t combinations[MAX_DIFFERENT_ADDR] = {0};

uint64_t indexes[MAX_DIFFERENT_ADDR] = { [0 ... MAX_DIFFERENT_ADDR - 1] = (uint64_t)(int64_t) -1};
uint64_t values[MAX_DIFFERENT_ADDR] = { 0};
uint64_t currentCombinations = 0;

void insertValue(uint64_t index, uint64_t val)
{
    for (int i = 0; i < MAX_DIFFERENT_ADDR; i++)
    {
        if (indexes[i] == index)
        {
            values[i] = val;
            return;
        }

        if (indexes[i] == (uint64_t)(int64_t) -1)
        {
            indexes[i] = index;
            values[i] = val;
            return;
        }
    }

    printf("MAX_DIFFERENT_ADDR too small\n");
    exit(-1);
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int input[MAX_LINES];
    int i = 0;
    uint64_t _1mask = 0;
    uint64_t _xmask = 0;
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
            _1mask = 0x0000000000;

            for (int k = 0; k < currentCombinations; k++)
            {
                combinations[k] = 0;
            }

            currentCombinations = 0;

            for (int j = 0; j < BITMASK_SIZE; j++)
            {
                if (token[j] == 'X')
                {
                    if (currentCombinations == 0)
                    {
                        currentCombinations = 2;
                        combinations[0] = 0;
                        combinations[1] = 1ULL << (BITMASK_SIZE - j - 1);
                    }
                    else
                    {
                        memcpy(&combinations[currentCombinations], combinations, sizeof(uint64_t) * currentCombinations);

                        for (int k = currentCombinations; k < 2 * currentCombinations; k++)
                        {
                            combinations[k] |= 1ULL << (BITMASK_SIZE - j - 1);
                        }

                        currentCombinations *= 2;

                        if (currentCombinations > MAX_DIFFERENT_ADDR)
                        {
                            printf("MAX_DIFFERENT_ADDR too small\n");
                            exit(-1);
                        }
                    }
                }

                if (token[j] == '1')
                {
                    _1mask |= 1ULL << (BITMASK_SIZE - j - 1);
                }
            }

            while (token != NULL)
            {
                token = strtok(NULL, delimiter);
            }
        }
        else
        {
            char* delimiter = " []";
            char* token = strtok(line, delimiter);
            token = strtok(NULL, delimiter);
            uint64_t index = strtol(token, NULL, 10);
            index |= _1mask;
            strtok(NULL, delimiter);
            token = strtok(NULL, delimiter);
            uint64_t val = strtol(token, NULL, 10);

            for (int k = 0; k < currentCombinations; k++)
            {
                insertValue(index ^ combinations[k], val);
            }

            // clean
            while (token != NULL)
            {
                token = strtok(NULL, delimiter);
            }
        }

        i++;
    }

    uint64_t sum = 0;

    for (int i = 0; i < MAX_DIFFERENT_ADDR; i++)
    {
        sum += values[i];
    }

    printf("solution : %llu\n", sum);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
