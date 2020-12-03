#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000
#define LINE_LENGTH 31

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

    int position = 0;
    int treeCount = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[position] == '#')
            treeCount++;

        position = (position + 3) % LINE_LENGTH;
    }

    printf("tree count : %d\n", treeCount);

    if (line)
        free(line);

    fclose(fp);
}
