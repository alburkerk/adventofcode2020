#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000
#define MAX_DIFFERENT_ANSWER 26
#define MAX_PEOPLE_PER_GROUP 10

int answerCount(char* data)
{
    int count = 0;
    // number of people in one group
    int peopleCount = 0;
    char answerMap[MAX_PEOPLE_PER_GROUP][MAX_DIFFERENT_ANSWER];

    // clean
    for (int i = 0; i < MAX_PEOPLE_PER_GROUP; i++)
        for (int j = 0; j < MAX_DIFFERENT_ANSWER; j++)
        {
            answerMap[i][j] = 0;
        }

    char delimiter[2] = "\n";
    char* singlePersonAnswer = strtok(data, delimiter);

    while (singlePersonAnswer != NULL)
    {
        for (int i = 0; i < strlen(singlePersonAnswer); i++)
        {
            answerMap[peopleCount][singlePersonAnswer[i] - 'a'] = 1;
        }

        peopleCount++;
        singlePersonAnswer = strtok(NULL, delimiter);
    }

    for (int i = 0; i < MAX_DIFFERENT_ANSWER; i++)
    {
        int singleAnswerCount = 1;

        for (int j = 0; j < peopleCount; j++)
        {
            if (answerMap[j][i] == 0)
            {
                singleAnswerCount = 0;
            }
        }

        count += singleAnswerCount;
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
