#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int adapters[MAX_LINES];
    int i = 0;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        adapters[i] = strtol(line, NULL, 10);
        i++;
    }

    int currentJoltage = 0;
    int _1jolDiffCount = 0;
    int _3jolDiffCount = 0;

    while (1)
    {
start:
        for (int k = 1; k <= 3; k++)
        {
            for (int j = 0; j < i; j++)
            {
                if (currentJoltage + k == adapters[j])
                {
                    currentJoltage = adapters[j];

                    if (k == 1)
                    {
                        _1jolDiffCount++;
                    }

                    if (k == 3)
                    {
                        _3jolDiffCount++;
                    }

                    goto start;
                }
            }
        }
        break;
    }

    _3jolDiffCount++;
    printf("solution is %d\n", _1jolDiffCount * _3jolDiffCount);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
