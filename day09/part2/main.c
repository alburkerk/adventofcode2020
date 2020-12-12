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

    int index1 = 0;
    int continuousIndexes = 1;
    // from part1
    int expectedSum = 530627549;
    int min, max;

    for (index1 = 0;  index1 < i; index1++)
    {
        int sum = 0;
        min = expectedSum;
        max = 0;

        for (continuousIndexes = 0; sum < expectedSum; continuousIndexes++)
        {
            sum += stream[index1 + continuousIndexes];
            if(stream[index1 + continuousIndexes] > max)
                max = stream[index1 + continuousIndexes];
            if(stream[index1 + continuousIndexes] < min)
                min = stream[index1 + continuousIndexes];
        }

        if (sum == expectedSum)
        {
            break;
        }
    }


    printf("solution is index1 : %d, continuousIndexes: %d, sum %d\n", index1, continuousIndexes , min + max);

    printf("\n\ndetail\n");
    int sum = 0;
    for(int j = index1; j < index1 + continuousIndexes; j++){
        printf(" stream[%d] = %d\n", j, stream[j]);
        sum += stream[j];
    }
    printf("\n sum : %d\n", sum);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
