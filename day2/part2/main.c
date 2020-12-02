#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000

typedef struct {
    int pos1;
    int pos2;
    char letter;
    char password[40];
} Policy;

int main(void)
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    Policy policies[MAX_LINES];
    int i = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("input not found");
        exit(EXIT_FAILURE);
    }

    const char* separators = "-: ";

    while ((read = getline(&line, &len, fp)) != -1) {
        char * strToken = strtok(line, separators);
        policies[i].pos1 =  strtol(strToken, NULL, 10);
        strToken = strtok(NULL, separators);
        policies[i].pos2 =  strtol(strToken, NULL, 10);
        strToken = strtok(NULL, separators);
        policies[i].letter = strToken[0];
        strToken = strtok(NULL, separators);
        strcpy(policies[i].password, strToken);
        i++;
    }

    int badPasswordCount = 0;

    for(int j = 0; j < i; j++) {
        char charPos1 = policies[j].password[policies[j].pos1 - 1];
        char charPos2 = policies[j].password[policies[j].pos2 - 1];

        if((charPos1 != policies[j].letter && charPos2 != policies[j].letter) || (charPos1 == policies[j].letter && charPos2 == policies[j].letter))
            badPasswordCount++;
    }

    printf("good password count : %d\n", i - badPasswordCount);

    if (line)
        free(line);

    fclose(fp);
}
