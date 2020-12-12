#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 4000

typedef struct {
    int min;
    int max;
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
        policies[i].min =  strtol(strToken, NULL, 10);
        strToken = strtok(NULL, separators);
        policies[i].max =  strtol(strToken, NULL, 10);
        strToken = strtok(NULL, separators);
        policies[i].letter = strToken[0];
        strToken = strtok(NULL, separators);
        strcpy(policies[i].password, strToken);
        i++;
    }

    int letterCount = 0;
    int badPasswordCount = 0;

    for(int j = 0; j < i; j++) {
        letterCount = 0;
        for(int k = 0; policies[j].password[k] != '\0'; k++) {
            if (policies[j].password[k] == policies[j].letter)
                letterCount++;
        }
        if (letterCount > policies[j].max || letterCount < policies[j].min)
            badPasswordCount++;
    }

    printf("good password count : %d\n", i - badPasswordCount);

    if (line)
        free(line);

    fclose(fp);
}
