#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000
#define LINE_LENGTH 31
#define NUMBER_OF_SLOPES 5

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    char map[MAX_LINES][LINE_LENGTH];

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    int treeCount[NUMBER_OF_SLOPES] = {0};
    int slopes[NUMBER_OF_SLOPES][2] = {
        { 1, 1},
        { 3, 1},
        { 5, 1},
        { 7, 1},
        { 1, 2}
    };
    int positionPerSlope[NUMBER_OF_SLOPES] = {0};
    int lineNumber = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        for (int i = 0; i < NUMBER_OF_SLOPES; i++) {
            if (lineNumber % slopes[i][1] != 0)
                continue;

            if (line[positionPerSlope[i]] == '#')
                treeCount[i]++;

            positionPerSlope[i] = (positionPerSlope[i] + slopes[i][0]) % LINE_LENGTH;
        }

        lineNumber++;
    }

    unsigned long result = 1;
    for (int i = 0; i < NUMBER_OF_SLOPES; i++) {
        printf("trees[%d] = %d\n", i, treeCount[i]);
        result *= treeCount[i];
    }

    printf("result : %ld\n", result);

    if (line)
        free(line);

    fclose(fp);
}
