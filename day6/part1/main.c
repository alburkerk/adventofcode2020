#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000

int answerCount(char* data)
{
    int count = 0;
    char buffer[2] = { '\0', '\0'};

    for (buffer[0] = 'a'; buffer[0] <= 'z'; buffer[0]++)
    {
        if (strstr(data, buffer) != NULL)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    char singleAnswer[400] = "";
    int yesCount = 0;
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
            yesCount += answerCount(singleAnswer);
            singleAnswer[0] = '\0';
        }

        strcat(singleAnswer, line);
    }

    // count last answer
    yesCount += answerCount(singleAnswer);
    printf("yes answer count : %d\n", yesCount);

    if (line)
    {
        free(line);
    }

    fclose(fp);
}
