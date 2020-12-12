#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 4000
#define CYPHER_SIZE 25

int isValid(int* stream, int index)
{
    for (int i = index - 1; i >= index - CYPHER_SIZE; i--)
    {
        for (int j  = i - 1; j >= index - CYPHER_SIZE; j--)
        {
            if (stream[i] + stream[j] == stream[index])
            {
                return 1;
            }
        }
    }

    return 0;
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    fp = fopen("input.txt", "r");
    int stream[MAX_LINES];

    if (fp == NULL)
    {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        stream[i] = strtol(line, NULL, 10);
        i++;
    }

    int j = CYPHER_SIZE;
    for (; j < i; j++)
    {
        if(!isValid(stream, j))
                break;
    }

    printf("solution is stream[%d] = %d\n", j ,stream[j]);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
